from typing import Any, Dict
from node import OutPort, Node

local_AST = Any


def _DAG_to_AST(compute_dag: Any, memory_dag: Dict[OutPort, Any], traversal_order: Dict[Node, Any])->local_AST:
    return None

