from compute_graph.DAG.node import *

def assert_in_port_exists(node_port:InPort):
    node, port = node_port
    if port>=node.num_inputs or port<0:
        raise PortDoesntExist(f"Input port {port} for node {node}")


def assert_out_port_exists(node_port:OutPort):
    node, port = node_port
    if port>=node.num_outputs or port<0:
        raise PortDoesntExist(f"Output port {port} for node {node}")



def _check_if_acyclic_r(cur_node_port:OutPort, edges: GraphEdges, visited: Set[Node], call_stack: List[Node])->List[ErrorMessage]:
    cur_node, _ = cur_node_port
    cs_copy = list(call_stack)
    cs_copy.append(cur_node)
    visited.add(cur_node)

    errors:List[ErrorMessage] = []
    for n,_ in edges[cur_node_port]:
        if n in cs_copy:
            errors.append(f"Cycle: {cs_copy[cs_copy.index(n):]}->{cur_node}->{n}")

        if n not in visited:
            for p in range(n.num_outputs):
                errors += _check_if_acyclic_r(OutPort((n,p)), edges, visited, cs_copy)
        
    return errors

def check_if_acyclic(start_nodes: Set[Node], edges: GraphEdges)->List[ErrorMessage]:
    start_ports: Set[OutPort] = set([OutPort((n, p)) for n in start_nodes for p in range(n.num_outputs)])

    errors:List[ErrorMessage]=[]
    for sp in start_ports:
        errors+=_check_if_acyclic_r(sp, edges, set(), [])
    
    return errors




