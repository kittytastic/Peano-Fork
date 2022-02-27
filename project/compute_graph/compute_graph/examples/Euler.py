from compute_graph.DAG import *
from compute_graph.DAG.ops import Divide
from compute_graph.DAG.primitive_node import Constant
from compute_graph.DAG.transform import DAG_Flatten, DAG_TransformChain, DAG_Viz
from compute_graph.DAG.visualize import visualize_graph
from compute_graph.IR.transform import IR_TransformChain
from compute_graph.main import dag_to_IR
from compute_graph.IR.misc import IR_TF_STOP, DefineAllVars, FileApplyCallStencil, FilterApply, FunctionStencil, InlineInOut, RemoveAllTemp, RemoveBackwardsAlias, RemoveForwardAlias
from compute_graph.IR.symbols import IR_Array, IR_SingleVariable, UniqueVariableName
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

if __name__=="__main__":
    g = flux_y()
    #g=irho_graph()
    #g=p_graph()
    
    visualize_graph(g, out_path="../Artifacts", max_depth=1)


    in1 = IR_Array(UniqueVariableName("input"), 4)
    out1 = IR_Array(UniqueVariableName("out"), 4)
    
    in3 = IR_Array(UniqueVariableName("in_p"), 4)
    out3 = IR_Array(UniqueVariableName("out_p"), 1)
    
    in4 = IR_Array(UniqueVariableName("in_irho"), 1)
    out4 = IR_Array(UniqueVariableName("out_irho"), 1)
    
    func_stencil:FunctionStencil = {
        'flux_x': ([in1, out1], in1.all_ref(), out1.all_ref()),
        'p': ([in3, out3], in3.all_ref(), out3.all_ref()),
        'irho': ([in4, out4], in4.all_ref(), out4.all_ref())
    }

    
    tf_stack = FullStackTransform(
        DAG_TransformChain([
            DAG_Viz(file_name = "before", max_depth=2),
            DAG_Flatten(),
            DAG_Viz(file_name = "after", max_depth=1),
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
