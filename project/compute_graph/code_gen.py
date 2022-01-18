from typing import Any, Dict
from node import OutPort, Node
from main import basic_graph
from graph import visualize_graph

local_AST = Any


def _DAG_to_AST(compute_dag: Any, memory_map: Dict[OutPort, Any], traversal_order: Dict[Node, Any])->local_AST:
    print(g.ast_visit())
    
    return None



if __name__=="__main__":
    g = basic_graph()
    visualize_graph(g)


    _DAG_to_AST(g, {}, {})