from ops import Add, Multiply, Subtract
from enum import Enum
from typing import Any, Dict, List, Tuple
from node import OutPort, Node
from graph import Graph, visualize_graph
from compute_graph.AST.ast_node_base import AST_Node
from project.compute_graph.AST.ast_nodes_g import AST_Add, AST_GetArray

class VariableType(Enum):
    INLINE = 1
    LOCAL = 2
    ARRAY = 3
    ARRAY_MEMBER = 4

memory_value = Tuple[VariableType, str, int]


def _DAG_to_AST(compute_dag: Graph, memory_map: Dict[OutPort, memory_value], traversal_order: List[Node])->AST_Node:
    dag_nodes = compute_dag.get_sub_nodes()
    print(f"DAG contains: {len(dag_nodes)} nodes")

    variable_stack = {}

    for v in memory_map.values():
        pass

    #node_ast: Dict[Node, AST_Node] = {}


    #for n in traversal_order:
    #    node_ast[n] = n.ast_visit([])

    return AST_Add(AST_GetArray(0), AST_GetArray(1))

def basic_graph()->Tuple[Graph, Dict[OutPort, memory_value], List[Node]]:
    g=Graph(2,3)
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

    # Memory map
    mm: Dict[OutPort, memory_value] = {}
    mm[g.get_internal_input(0)] = (VariableType.INLINE, "", -1)
    mm[g.get_internal_input(1)] = (VariableType.INLINE, "", -1)
    mm[OutPort((add, 0))] = (VariableType.LOCAL, "add", -1)
    mm[OutPort((sub, 0))] = (VariableType.LOCAL, "sub", -1)
    mm[OutPort((mul, 0))] = (VariableType.LOCAL, "mul", -1)

    # Traversal order
    in_1, _ = g.get_internal_input(0)
    in_2, _ = g.get_internal_input(0)
    to:List[Node] = [in_1, in_2, add, sub, mul]


    return (g, mm, to)

if __name__=="__main__":
    g, mm, to = basic_graph()
    visualize_graph(g)


    _DAG_to_AST(g, mm, to)