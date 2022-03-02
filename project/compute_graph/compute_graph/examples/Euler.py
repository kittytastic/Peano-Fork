from typing import Callable, List
from compute_graph.DAG import *
from compute_graph.DAG.graph import DAG_Message
from compute_graph.DAG.ops import Divide, Sqrt
from compute_graph.DAG.primitive_node import Constant
from compute_graph.DAG.transform import DAG_Flatten, DAG_TransformChain, DAG_Viz
from compute_graph.DAG.visualize import visualize_graph
from compute_graph.IR.transform import IR_TransformChain
from compute_graph.IR.misc import IR_TF_STOP, DefineAllVars, FileApplyCallStencil, FilterApply, FunctionStencil,  RemoveAllTemp, RemoveBackwardsAlias, RemoveForwardAlias
from compute_graph.IR.symbols import IR_Array,  UniqueVariableName
from compute_graph.IR.symbols.functions import  IR_LooseFunction, IR_TightFunction
from compute_graph.language_backend.c import C_Backend
from compute_graph.transform import FullStackTransform

def irho_graph()->Graph:
    g = Graph(1,1, "irho")
    div = Divide()
    c1 = Constant(1)

    g.add_edge((c1, 0), (div, 0))
    g.add_edge(g.get_internal_input(0), (div, 1))

    g.add_edge((div, 0), g.get_internal_output(0))

    return g

def p_graph()->Graph:
    #(gamma-1) * (Q[3] - 0.5*irho*(Q[1]*Q[1]+Q[2]*Q[2]))
    g = Graph(4,1, 'p')

    c1 = Constant(0.4)
    c2 = Constant(0.5)


    sub1 = Subtract()
    add1 = Add(2)
    mul1 = Multiply(2)
    mul2 = Multiply(2)
    mul3 = Multiply(2)
    mul4 = Multiply(2)
    mul5 = Multiply(2)

    # Q[1]*Q[1]
    g.add_edge(g.get_internal_input(1), (mul1, 0))
    g.add_edge(g.get_internal_input(1), (mul1, 1))

    # Q[2]*Q[2]
    g.add_edge(g.get_internal_input(2), (mul2, 0))
    g.add_edge(g.get_internal_input(2), (mul2, 1))

    # (Q1[1]*Q1[1]+Q[2]*Q[2])
    g.fill_node_inputs([(mul1, 0), (mul2, 0)], add1)

    # irho * (Q1[1]...Q[2])
    g.fill_node_inputs([(add1, 0), g.get_internal_input(0)], mul3)
    
    # 0.5 * irho * (Q1[1]...Q[2])
    g.fill_node_inputs([(c2,0), (mul3, 0)], mul4)

    # Q[3] - 0.5 * ...
    g.fill_node_inputs([g.get_internal_input(3), (mul4, 0)], sub1)
    
    # 0.4 * (Q[3] - ...)
    g.fill_node_inputs([(c1,0), (sub1,0)], mul5)


    g.add_edge((mul5, 0), g.get_internal_output(0))

    return g



def flux_x()->Graph:
    g = Graph(4,4, "flux_x")
    p = p_graph()
    irho = irho_graph()

    mul1 = Multiply(3)
    mul2 = Multiply(3)
    mul3 = Multiply(3)

    add1 = Add(2)
    add2 = Add(2)

    # p
    g.fill_node_inputs([(irho, 0), g.get_internal_input(1), g.get_internal_input(2), g.get_internal_input(3)], p) 

    # irho
    g.add_edge(g.get_internal_input(0), (irho, 0))


    # F[0]
    g.add_edge(g.get_internal_input(1), g.get_internal_output(0))

    # F[1]
    g.fill_node_inputs([(irho,0), g.get_internal_input(1),g.get_internal_input(1)], mul1)
    g.fill_node_inputs([(mul1, 0), (p, 0)], add1)
    g.add_edge((add1, 0), g.get_internal_output(1))

    # F[2]
    g.fill_node_inputs([(irho,0), g.get_internal_input(1), g.get_internal_input(2)], mul2)
    g.add_edge((mul2, 0), g.get_internal_output(2))

    # F[3]
    g.fill_node_inputs([g.get_internal_input(3), (p,0)], add2)
    g.fill_node_inputs([(irho,0), g.get_internal_input(1), (add2, 0)], mul3)
    g.add_edge((mul3, 0), g.get_internal_output(3))

    return g

def flux_y()->Graph:
    g = Graph(4,4, "flux_y")
    p = p_graph()
    irho = irho_graph()

    mul1 = Multiply(3)
    mul2 = Multiply(3)
    mul3 = Multiply(3)

    add1 = Add(2)
    add2 = Add(2)

    # p
    g.fill_node_inputs([(irho, 0), g.get_internal_input(1), g.get_internal_input(2), g.get_internal_input(3)], p) 

    # irho
    g.add_edge(g.get_internal_input(0), (irho, 0))


    # F[0]
    g.add_edge(g.get_internal_input(2), g.get_internal_output(0))

    # F[1]
    g.fill_node_inputs([(irho,0), g.get_internal_input(2), g.get_internal_input(1)], mul2)
    g.add_edge((mul2, 0), g.get_internal_output(2))

    # F[2]
    g.fill_node_inputs([(irho,0), g.get_internal_input(2), g.get_internal_input(2)], mul1)
    g.fill_node_inputs([(mul1, 0), (p, 0)], add1)
    g.add_edge((add1, 0), g.get_internal_output(1))

    # F[3]
    g.fill_node_inputs([g.get_internal_input(3), (p,0)], add2)
    g.fill_node_inputs([(irho,0), g.get_internal_input(2), (add2, 0)], mul3)
    g.add_edge((mul3, 0), g.get_internal_output(3))

    return g

def max_eigen_x():
    g = Graph(4,1, "max_eigen_x")
    p = p_graph()
    irho = irho_graph()

    mul1 = Multiply(3)
    mul2 = Multiply(2)

    add1 = Add(2)
    sub1 = Subtract()

    abs1 = Abs()
    abs2 = Abs()
    max1 = Max(2)
    sqrt1 = Sqrt()

    c1 = Constant(0.4)

    # p
    g.fill_node_inputs([(irho, 0), g.get_internal_input(1), g.get_internal_input(2), g.get_internal_input(3)], p) 

    # irho
    g.add_edge(g.get_internal_input(0), (irho, 0))


    # c
    g.fill_node_inputs([(c1,0), (p,0), (irho, 0)], mul1)
    g.fill_node_inputs([(mul1, 0)], sqrt1)

    # Q[1] * irho
    g.fill_node_inputs([g.get_internal_input(1), (irho,0)], mul2)
    
    # max
    g.fill_node_inputs([(mul2, 0), (sqrt1,0)], sub1)
    g.fill_node_inputs([(sub1, 0)], abs1)
    g.fill_node_inputs([(mul2, 0), (sqrt1,0)], add1)
    g.fill_node_inputs([(add1, 0)], abs2)
    g.fill_node_inputs([(abs1,0), (abs2,0)], max1)
    
    g.add_edge((max1, 0), g.get_internal_output(0))

    return g

def max_eigen_y():
    g = Graph(4,1, "max_eigen_y")
    p = p_graph()
    irho = irho_graph()

    mul1 = Multiply(3)
    mul2 = Multiply(2)

    add1 = Add(2)
    sub1 = Subtract()

    abs1 = Abs()
    abs2 = Abs()
    max1 = Max(2)
    sqrt1 = Sqrt()

    c1 = Constant(0.4)

    # p
    g.fill_node_inputs([(irho, 0), g.get_internal_input(1), g.get_internal_input(2), g.get_internal_input(3)], p) 

    # irho
    g.add_edge(g.get_internal_input(0), (irho, 0))


    # c
    g.fill_node_inputs([(c1,0), (p,0), (irho, 0)], mul1)
    g.fill_node_inputs([(mul1, 0)], sqrt1)

    # Q[1] * irho
    g.fill_node_inputs([g.get_internal_input(2), (irho,0)], mul2)
    
    # max
    g.fill_node_inputs([(mul2, 0), (sqrt1,0)], sub1)
    g.fill_node_inputs([(sub1, 0)], abs1)
    g.fill_node_inputs([(mul2, 0), (sqrt1,0)], add1)
    g.fill_node_inputs([(add1, 0)], abs2)
    g.fill_node_inputs([(abs1,0), (abs2,0)], max1)
    
    g.add_edge((max1, 0), g.get_internal_output(0))

    return g


def rusanov(max_eigen_builder: Callable[[], Graph], flux_builder: Callable[[], Graph], friendly_name:str="rusanov")->Graph:
    g = Graph(8, 4, friendly_name)
    flux_l = flux_builder()
    flux_r = flux_builder()

    eigen_l = max_eigen_builder()
    eigen_r = max_eigen_builder()

    # Flux L
    g.add_edge(g.get_internal_input(0), flux_l.get_external_input(0))
    g.add_edge(g.get_internal_input(1), flux_l.get_external_input(1))
    g.add_edge(g.get_internal_input(2), flux_l.get_external_input(2))
    g.add_edge(g.get_internal_input(3), flux_l.get_external_input(3))
    
    # Flux R
    g.add_edge(g.get_internal_input(4), flux_r.get_external_input(0))
    g.add_edge(g.get_internal_input(5), flux_r.get_external_input(1))
    g.add_edge(g.get_internal_input(6), flux_r.get_external_input(2))
    g.add_edge(g.get_internal_input(7), flux_r.get_external_input(3))

    # Lambda Max L
    g.add_edge(g.get_internal_input(0), eigen_l.get_external_input(0))
    g.add_edge(g.get_internal_input(1), eigen_l.get_external_input(1))
    g.add_edge(g.get_internal_input(2), eigen_l.get_external_input(2))
    g.add_edge(g.get_internal_input(3), eigen_l.get_external_input(3))
    
    # Lambda Max R
    g.add_edge(g.get_internal_input(4), eigen_r.get_external_input(0))
    g.add_edge(g.get_internal_input(5), eigen_r.get_external_input(1))
    g.add_edge(g.get_internal_input(6), eigen_r.get_external_input(2))
    g.add_edge(g.get_internal_input(7), eigen_r.get_external_input(3))

    l_max = Max(2)
    g.fill_node_inputs([(eigen_l, 0), (eigen_r, 0)], l_max)

    for i in range(4):
        h = Constant(0.5)
        mul1 = Multiply(2)
        mul2 = Multiply(2)
        mul3 = Multiply(3)
        sub1 = Subtract()
        sub2 = Subtract()
        add1 = Add(2)

        # QR - QL
        g.fill_node_inputs([g.get_internal_input(i), g.get_internal_input(i+4)], sub1)
        # 0.5 * lmax * (...)
        g.fill_node_inputs([h, l_max, sub1], mul3)

        # 0.5 * FL + 0.5 * FR
        g.fill_node_inputs([h, (flux_l, i)], mul1)
        g.fill_node_inputs([h, (flux_r, i)], mul2)
        g.fill_node_inputs([mul1, mul2], add1)

        g.fill_node_inputs([mul3, add1], sub2)

        g.add_edge((sub2, 0), g.get_internal_output(i))
    
    return g

def patchUpdate(patch_len: int, dim: int, unknowns: int, rusanov_x:Callable[[str], Graph], rusanov_y:Callable[[str], Graph])->Graph:
    Qins:int = (patch_len+2)**dim * unknowns
    Qout:int = (patch_len)**dim * unknowns

    Q_in_start = 0
    t = Q_in_start + Qins
    dt = t+1
    patch_center_base = dt + 1
    patch_size_base = patch_center_base + dim
    total_ins = patch_size_base+dim

    print(f"Total inputs: {total_ins}")
    print(f"Qin size: {Qins}")
    print(f"Qout size: {Qout}")
    g=Graph(total_ins, Qout, "PatchUpdate")

    Q_out_pos_contrib:List[List[OutPort]] = [[] for _ in range(Qout)]
    Q_out_neg_contrib:List[List[OutPort]] = [[] for _ in range(Qout)]

    dt_div_size = Constant(1)

    # Flux x
    for x in range(patch_len+1):
        for y in range(patch_len):
            leftVoxelInPreImage = voxelInPreimage(x-1, y, patch_len)
            rightVoxelInPreImage = voxelInPreimage(x, y, patch_len)

            leftVoxelInImage = voxelInImage(x-1, y, patch_len)
            rightVoxelInImage = voxelInImage(x, y, patch_len)

            # SKIP volumeX - not used in rusanov

            # Rusanov
            rus = rusanov_x(f"rusanov-x ({x}, {y})")
            for u in range(unknowns): g.add_edge(g.get_internal_input(Q_in_start + leftVoxelInPreImage*unknowns + u), rus.get_external_input(u))
            for u in range(unknowns): g.add_edge(g.get_internal_input(Q_in_start + rightVoxelInPreImage*unknowns + u), rus.get_external_input(u+unknowns))

            # Update out
            for u in range(unknowns):
                if x>0:
                    Q_out_neg_contrib[leftVoxelInImage*unknowns+u].append(rus.get_external_output(u))

                if x<patch_len:
                    Q_out_pos_contrib[rightVoxelInImage*unknowns+u].append(rus.get_external_output(u))


    
    # Flux y
    for x in range(patch_len):
        for y in range(patch_len+1):
            leftVoxelInPreImage = voxelInPreimage(x, y-1, patch_len)
            rightVoxelInPreImage = voxelInPreimage(x, y, patch_len)

            leftVoxelInImage = voxelInImage(x, y-1, patch_len)
            rightVoxelInImage = voxelInImage(x, y, patch_len)

            # SKIP volumeX - not used in rusanov

            # Rusanov
            rus = rusanov_y(f"rusanov-y ({x}, {y})")
            for u in range(unknowns): g.add_edge(g.get_internal_input(Q_in_start + leftVoxelInPreImage*unknowns + u), rus.get_external_input(u))
            for u in range(unknowns): g.add_edge(g.get_internal_input(Q_in_start + rightVoxelInPreImage*unknowns + u), rus.get_external_input(u+unknowns))

            # Update out
            for u in range(unknowns):
                if y>0:
                    Q_out_neg_contrib[leftVoxelInImage*unknowns+u].append(rus.get_external_output(u))

                if y<patch_len:
                    Q_out_pos_contrib[rightVoxelInImage*unknowns+u].append(rus.get_external_output(u))

    for i in range(Qout):
        add_pos = Add(len(Q_out_pos_contrib[i]))
        add_neg = Add(len(Q_out_neg_contrib[i]))
        diff = Subtract()
        scale = Multiply(2)

        g.fill_node_inputs(Q_out_pos_contrib[i], add_pos) # type:ignore
        g.fill_node_inputs(Q_out_neg_contrib[i], add_neg) # type:ignore
        g.fill_node_inputs([add_pos, add_neg], diff)
        g.fill_node_inputs([diff, dt_div_size], scale)
        g.add_edge((scale, 0), g.get_internal_output(i))
    
    return g

def voxelInPreimage(x: int, y:int, patch_len: int): return x+1 + (y+1) * (2+patch_len)
def voxelInImage(x: int, y:int, patch_len: int): return x + y * patch_len

if __name__=="__main__":
    make_rus_x:Callable[[str], Graph] = lambda x: rusanov(max_eigen_x, flux_x, friendly_name=x)
    make_rus_y:Callable[[str], Graph] = lambda x: rusanov(max_eigen_y, flux_y, friendly_name=x)
    g = patchUpdate(3, 2, 4, make_rus_x, make_rus_y)
    #g = rusanov(max_eigen_x, flux_x)
    #g=irho_graph()
    #g=p_graph()
    
    errs = g.validate()
    DAG_Message.print_summary(errs, 10)
    visualize_graph(g, out_path="../Artifacts", max_depth=1)


    in1 = IR_Array(UniqueVariableName("input"), 4)
    out1 = IR_Array(UniqueVariableName("out"), 4)
    
    in3 = IR_Array(UniqueVariableName("in_p"), 4)
    out3 = IR_Array(UniqueVariableName("out_p"), 1)
    
    in4 = IR_Array(UniqueVariableName("in_irho"), 1)
    out4 = IR_Array(UniqueVariableName("out_irho"), 1)

    in5 = IR_Array(UniqueVariableName("in_max_eig_x"), 4)
    out5 = IR_Array(UniqueVariableName("out_max_eig_x"), 1)
    
    in6 = IR_Array(UniqueVariableName("in_max_eig_y"), 4)
    out6 = IR_Array(UniqueVariableName("out_max_eig_y"), 1)
    
    in7 = IR_Array(UniqueVariableName("in_rusanov"), 8)
    out7 = IR_Array(UniqueVariableName("out_rusanov"), 4)
    
    func_stencil:FunctionStencil = {
        'flux_x': ([in1, out1], in1.all_ref(), out1.all_ref()),
        'max_eigen_x': ([in5, out5], in5.all_ref(), out5.all_ref()),
        'max_eigen_y': ([in6, out6], in6.all_ref(), out6.all_ref()),
        'rusanov': ([in7, out7], in7.all_ref(), out7.all_ref()),
        'p': ([in3, out3], in3.all_ref(), out3.all_ref()),
        'irho': ([in4, out4], in4.all_ref(), out4.all_ref())
    }

    
    tf_stack = FullStackTransform(
        DAG_TransformChain([
            DAG_Viz(file_name = "before", max_depth=1),
            #DAG_Flatten(),
            DAG_Viz(file_name = "after", max_depth=None),
        ]),
        IR_TransformChain([
            #IR_TF_STOP(),
            FilterApply(IR_LooseFunction, RemoveForwardAlias()),
            FilterApply(IR_LooseFunction, RemoveBackwardsAlias()),
            FileApplyCallStencil(func_stencil),
            FilterApply(IR_TightFunction, RemoveAllTemp()),
            FilterApply(IR_TightFunction, DefineAllVars()),
        ],
        verbose=True),
        C_Backend()
    )
    
    code = tf_stack.tf(g)

    print(code)
