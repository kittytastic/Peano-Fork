from typing import Dict, List, Tuple

from compute_graph.ops import Add, Multiply, Subtract
from compute_graph.node import OutPort, Node
from compute_graph.graph import Graph, visualize_graph
from compute_graph.AST.variables import VariableReference, LocalVar
from compute_graph.kernel import Kernel



def basic_graph()->Tuple[Graph, Dict[OutPort, VariableReference], List[Node]]:
    # Graph Nodes
    g = Graph(2,3)
    add = Add(2)
    mul = Multiply(2)
    sub = Subtract()
    
    # Graph    
    g.add_edge(g.get_internal_input(0), (add,0))
    g.add_edge(g.get_internal_input(1), (add,1))
    g.add_edge((add,0), g.get_internal_output(0))
    
    g.add_edge(g.get_internal_input(0), (sub,0))
    g.add_edge(g.get_internal_input(1), (sub,1))
    g.add_edge((sub,0), g.get_internal_output(2))

    g.add_edge((sub, 0), (mul,0))
    g.add_edge((add, 0), (mul,1))
    g.add_edge((mul, 0), g.get_internal_output(1))

    # Variables + References
    v_t1 = LocalVar("temp1")
    v_t1_ref = v_t1.get_references()[0]
    v_t2 = LocalVar("temp2")
    v_t2_ref = v_t2.get_references()[0]
    v_add = LocalVar("add")
    v_add_ref = v_add.get_references()[0]
    v_sub = LocalVar("sub")
    v_sub_ref = v_sub.get_references()[0]
    v_mul = LocalVar("mul")
    v_mul_ref = v_mul.get_references()[0]

    # Memory map
    mm: Dict[OutPort, VariableReference] = {}
    mm[g.get_internal_input(0)] = v_t1_ref
    mm[g.get_internal_input(1)] = v_t2_ref
    mm[OutPort((add, 0))] = v_add_ref
    mm[OutPort((sub, 0))] = v_sub_ref
    mm[OutPort((mul, 0))] = v_mul_ref

    # Traversal order
    in_1, _ = g.get_internal_input(0)
    in_2, _ = g.get_internal_input(0)
    to:List[Node] = [in_1, in_2, add, sub, mul]

    visualize_graph(g)
    
    # Variables + References
    v_i1 = LocalVar("in1")
    v_i1_ref = v_i1.get_references()[0]
    v_i2 = LocalVar("in2")
    v_i2_ref = v_i2.get_references()[0]
    
    v_o1 = LocalVar("out1")
    v_o1_ref = v_o1.get_references()[0]
    v_o2 = LocalVar("out2")
    v_o2_ref = v_o2.get_references()[0]
    v_o3 = LocalVar("out3")
    v_o3_ref = v_o3.get_references()[0]
    
    k = Kernel([v_i1, v_i2], [v_o1, v_o2, v_o3])
    kernel_dag_map = {
        v_i1_ref: g.get_external_input(0),
        v_i2_ref: g.get_external_input(1)
    }
    dag_kernel_map = {
        g.get_external_output(0): v_o1_ref,
        g.get_external_output(1): v_o2_ref,
        g.get_external_output(2): v_o3_ref,
    }

    k.set_DAG(g, kernel_dag_map, dag_kernel_map)

    ast = k.ast_compile(mm, to)

    print(ast)
    return (g, mm, to)


def most_basic():
    # Graph Nodes
    g = Graph(2,1)
    add = Add(2)
    
    # Graph    
    g.add_edge(g.get_internal_input(0), (add,0))
    g.add_edge(g.get_internal_input(1), (add,1))
    g.add_edge((add,0), g.get_internal_output(0))
    

    # Variables + References
    v_t1 = LocalVar("temp1")
    v_t1_ref = v_t1.get_references()[0]
    v_t2 = LocalVar("temp2")
    v_t2_ref = v_t2.get_references()[0]
    v_add = LocalVar("add")
    v_add_ref = v_add.get_references()[0]

    # Memory map
    mm: Dict[OutPort, VariableReference] = {}
    mm[g.get_internal_input(0)] = v_t1_ref
    mm[g.get_internal_input(1)] = v_t2_ref
    mm[OutPort((add, 0))] = v_add_ref

    # Traversal order
    in_1, _ = g.get_internal_input(0)
    in_2, _ = g.get_internal_input(0)
    to:List[Node] = [in_1, in_2, add]

    visualize_graph(g)
    
    # Variables + References
    v_i1 = LocalVar("in1")
    v_i1_ref = v_i1.get_references()[0]
    v_i2 = LocalVar("in2")
    v_i2_ref = v_i2.get_references()[0]
    
    v_o1 = LocalVar("out1")
    v_o1_ref = v_o1.get_references()[0]
    
    k = Kernel([v_i1, v_i2], [v_o1])
    kernel_dag_map = {
        v_i1_ref: g.get_external_input(0),
        v_i2_ref: g.get_external_input(1)
    }
    dag_kernel_map = {
        g.get_external_output(0): v_o1_ref,
    }

    k.set_DAG(g, kernel_dag_map, dag_kernel_map)

    ast = k.ast_compile(mm, to)

    print(ast)
    return (g, mm, to)



if __name__=="__main__":
    #basic_graph()
    most_basic()

