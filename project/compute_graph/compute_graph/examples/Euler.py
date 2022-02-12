from compute_graph.DAG import *
from compute_graph.DAG.visualize import visualize_graph
from compute_graph.main import dag_to_IR
from compute_graph.IR.misc import DefineAllVars, FileApplyCallStencil, FilterApply, FunctionStencil, InlineInOut, RemoveAllTemp
from compute_graph.IR.symbols import IR_Array, IR_SingleVariable, UniqueVariableName
from compute_graph.IR.symbols.functions import  IR_LooseFunction, IR_TightFunction
from compute_graph.language_backend.c import C_Backend

def irho_graph()->Graph:
    g = Graph(1,1, "irho")
    div = Multiply(2)
    g.add_edge(g.get_internal_input(0), (div, 0))
    g.add_edge(g.get_internal_input(0), (div, 1))

    g.add_edge((div, 0), g.get_internal_output(0))

    return g

def p_graph()->Graph:
    #(gamma-1) * (Q[3] - 0.5*irho*(Q[1]*Q[1]+Q[2]*Q[2]))
    g = Graph(4,1, 'p')

    sub1 = Subtract()
    add1 = Add(2)
    mul1 = Multiply(2)
    mul2 = Multiply(2)
    mul3 = Multiply(2)

    g.add_edge(g.get_internal_input(1), (mul1, 0))
    g.add_edge(g.get_internal_input(1), (mul1, 1))

    g.add_edge(g.get_internal_input(2), (mul2, 0))
    g.add_edge(g.get_internal_input(2), (mul2, 1))

    g.fill_node_inputs([(mul1, 0), (mul2, 0)], add1)

    g.fill_node_inputs([(add1, 0), g.get_internal_input(0)], mul3)

    g.fill_node_inputs([g.get_internal_input(3), (mul3, 0)], sub1)

    g.add_edge((sub1, 0), g.get_internal_output(0))

    return g



def Euler2D_X()->Graph:
    g = Graph(4,4, "Euler2d_X")
    p = p_graph()
    irho = irho_graph()

    mul1 = Multiply(3)
    mul2 = Multiply(3)
    mul3 = Multiply(3)

    add1 = Add(2)
    add2 = Add(2)

    # To P
    g.add_edge((irho, 0), (p,0))
    g.add_edge(g.get_internal_input(1), (p,1))
    g.add_edge(g.get_internal_input(2), (p,2))
    g.add_edge(g.get_internal_input(3), (p,3))

    # irho
    g.add_edge(g.get_internal_input(0), (irho, 0))


    # F[0]
    g.add_edge(g.get_internal_input(2), g.get_internal_output(0))

    # F[1]
    g.add_edge((irho,0), (mul1, 0))
    g.add_edge(g.get_internal_input(1), (mul1, 1))
    g.add_edge(g.get_internal_input(1), (mul1, 2))
    g.add_edge((mul1, 0), (add1, 0))
    g.add_edge((p, 0), (add1, 1))
    g.add_edge((add1, 0), g.get_internal_output(1))

    # F[2]
    g.add_edge((irho,0), (mul2, 0))
    g.add_edge(g.get_internal_input(1), (mul2, 1))
    g.add_edge(g.get_internal_input(2), (mul2, 2))
    g.add_edge((mul2, 0), g.get_internal_output(2))

    # F[3]
    g.add_edge((irho,0), (mul3, 0))
    g.add_edge(g.get_internal_input(1), (mul3, 1))
    g.add_edge(g.get_internal_input(3), (add2, 0))
    g.add_edge((p, 0), (add2, 1))
    g.add_edge((add2, 0), (mul3, 2))
    g.add_edge((mul3, 0), g.get_internal_output(3))

    return g

if __name__=="__main__":
    g = Euler2D_X()
    visualize_graph(g, out_path="../Artifacts", max_depth=1)


    func = dag_to_IR(g) 
    print('----- Dag -> IR -----')
    print(func)

    tf = FilterApply(IR_LooseFunction, InlineInOut())
    func = tf.tf(func)
    print("\n------ tf ------")
    print(func)


    in1 = IR_Array(UniqueVariableName("input"), 4)
    out1 = IR_Array(UniqueVariableName("out"), 4)
    
    in3 = IR_Array(UniqueVariableName("in_p"), 4)
    out3 = IR_Array(UniqueVariableName("out_p"), 1)
    
    in4 = IR_Array(UniqueVariableName("in_irho"), 1)
    out4 = IR_Array(UniqueVariableName("out_irho"), 1)
    
    func_stencil:FunctionStencil = {
        'Euler2d_X': ([in1, out1], in1.all_ref(), out1.all_ref()),
        'p': ([in3, out3], in3.all_ref(), out3.all_ref()),
        'irho': ([in4, out4], in4.all_ref(), out4.all_ref())
    }

    tf = FileApplyCallStencil(func_stencil)
    print("\n------ tf ------")
    func = tf.tf(func)
    print(func)


    tf3 = FilterApply(IR_TightFunction, RemoveAllTemp())
    func = tf3.tf(func)
    print("\n------ tf - remove temp ------")
    print(func)
    
    tf4 = FilterApply(IR_TightFunction, DefineAllVars())
    func = tf4.tf(func)
    print("\n------ tf - define all vars ------")
    print(func)
    
    cbe = C_Backend()
    code = cbe.code_gen(func)
    print()
    print(code)