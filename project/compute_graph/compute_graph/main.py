from compute_graph.DAG.IR_tf import DAGToIRVisitor
from compute_graph.DAG.graph import *
from compute_graph.DAG.ops import *
from compute_graph.DAG.visualize import visualize_graph
from compute_graph.IR.misc import ApplyCallStencil, DefineAllVars, InlineInOut, RemoveAllTemp
from compute_graph.IR.symbols import IR_Array, IR_SingleVariable
from compute_graph.IR.c_tf import compile_as_c

def Euler2D_X()->Graph:
    g = Graph(4,4)
    p = Multiply(4)
    irho = PassThroughNode(friendly_name="irho")

    mul1 = Multiply(3)
    mul2 = Multiply(3)
    mul3 = Multiply(3)

    add1 = Add(2)
    add2 = Add(2)

    # To P
    g.add_edge(g.get_internal_input(0), (p,0))
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

def basic_graph()->Graph:
    g=Graph(2,3)
    add = Add(2)
    mul = Multiply(2)
    sub = Subtract()
    
    
    g.add_edge(g.get_internal_input(0), (add,0))
    g.add_edge(g.get_internal_input(1), (add,1))
    g.add_edge((add,0), g.get_internal_output(0))
    
    g.add_edge(g.get_internal_input(0), (sub,0))
    g.add_edge(g.get_internal_input(1), (sub,1))
    g.add_edge((sub,0), g.get_internal_output(2))

    g.add_edge((sub, 0), (mul,0))
    g.add_edge((add, 0), (mul,1))
    g.add_edge((mul, 0), g.get_internal_output(1))

    return g

if __name__=="__main__":

    g = basic_graph()    
    visualize_graph(g)

    v = DAGToIRVisitor()
    func = v.visit(g, [])
    print(func)

    tf = InlineInOut()
    func = tf.tf(func)
    print()
    print(func)

    in1 = IR_SingleVariable("input1", False)
    in2 = IR_SingleVariable("input2", False)
    out = IR_Array("out", 3)
    tf2 = ApplyCallStencil([in1, in2, out], [in1, in2], [out.get_ref(0), out.get_ref(1), out.get_ref(2)])
    func = tf2.tf(func)
    print()
    print(func)

    tf3 = RemoveAllTemp()
    func = tf3.tf(func)
    print()
    print(func)
    
    tf4 = DefineAllVars()
    func = tf4.tf(func)
    print()
    print(func)

    code = compile_as_c(func)
    print()
    print(code)

    