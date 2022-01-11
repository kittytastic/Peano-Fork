from node import *

def assert_in_port_exists(node_port:InPort):
    node, port = node_port
    if port>=node.num_inputs or port<0:
        raise PortDoesntExist(f"Input port {port} for node {node}")


def assert_out_port_exists(node_port:OutPort):
    node, port = node_port
    if port>=node.num_outputs or port<0:
        raise PortDoesntExist(f"Output port {port} for node {node}")


