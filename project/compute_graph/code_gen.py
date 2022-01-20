from compute_graph.AST.ast_nodes_g import AST_Compound
from ops import Add, Multiply, Subtract
from enum import Enum
from typing import Any, Dict, List, Tuple
from node import InPort, OutPort, Node
from graph import Graph, visualize_graph
from compute_graph.AST.ast_node_base import AST_Node
from compute_graph.AST.variables import VariableReference
from compute_graph.AST.ast_nodes_g import AST_Add, AST_GetArray
from compute_graph.AST.variables import LocalVar


def _DAG_to_AST(compute_dag: Graph, memory_map: Dict[OutPort, VariableReference], traversal_order: List[Node])->AST_Node:
    dag_nodes = compute_dag.get_sub_nodes()
    print(f"DAG contains: {len(dag_nodes)} nodes")
    variables = set([vr.var for vr in memory_map.values()])
    inverse_edges = compute_dag.inverse_edges()
    
    
    dec_expr = [v.declare() for v in variables if v.declare() is not None]

    compute_expr:List[AST_Node] = []
    
    for n in traversal_order:
        in_port_connections = [inverse_edges[InPort((n, p))] for p in range(n.num_inputs)]
        in_port_var_ref = [memory_map[p] for p in in_port_connections]
        in_port_ast = [pvr.ref() for pvr in in_port_var_ref]

        node_ast = n.ast_visit(in_port_ast)

        out_port_store_var_ref = [memory_map[OutPort((n, p))] for p in range(n.num_outputs)]
        out_port_set_ast = [vr.set(ast) for vr, ast in zip(out_port_store_var_ref, node_ast)]

        compute_expr += out_port_set_ast

    body_ast = dec_expr+compute_expr

    return AST_Compound(body_ast)

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


    return (g, mm, to)

if __name__=="__main__":
    g, mm, to = basic_graph()
    visualize_graph(g)


    _DAG_to_AST(g, mm, to)