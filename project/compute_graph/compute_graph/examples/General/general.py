from typing import Callable

from compute_graph.DAG import *

def rusanov(
    unknowns:int,
    max_eigen_builder: Callable[[], Graph],
    flux_builder: Callable[[], Graph],
    friendly_name:str="rusanov")->Graph:

    # Q left (unknowns)
    # Q right (unknowns)
    # patch center (2)
    # patch dx     (1)
    # t            (1)
    # dt           (1)
    g = Graph(unknowns*2 + 2+1+1+1, unknowns*2, friendly_name)
    flux_l = flux_builder()
    flux_r = flux_builder()

    eigen_l = max_eigen_builder()
    eigen_r = max_eigen_builder()

    # Flux and Eigen
    for u in range(unknowns):
        g.add_edge(g.get_internal_input(u), flux_l.get_external_input(u))
        g.add_edge(g.get_internal_input(unknowns + u), flux_r.get_external_input(u))
        g.add_edge(g.get_internal_input(u), eigen_l.get_external_input(u))
        g.add_edge(g.get_internal_input(unknowns + u), eigen_r.get_external_input(u))

    for e in range(2+1+1+1):
        g.add_edge(g.get_internal_input(unknowns+e), flux_l.get_external_input(unknowns+e))
        g.add_edge(g.get_internal_input(unknowns+e), eigen_l.get_external_input(unknowns+e))
        g.add_edge(g.get_internal_input(unknowns+e), flux_r.get_external_input(unknowns+e))
        g.add_edge(g.get_internal_input(unknowns+e), eigen_r.get_external_input(unknowns+e))

    l_max = Max(2)
    g.fill_node_inputs([eigen_l, eigen_r], l_max)

    for i in range(unknowns):
        h = Constant(0.5)
        mul1 = Multiply(2)
        mul2 = Multiply(2)
        mul3 = Multiply(3)
        sub1 = Subtract()
        sub2 = Subtract()
        add1 = Add(2)

        # QR - QL
        g.fill_node_inputs([g.get_internal_input(i+unknowns), g.get_internal_input(i)], sub1)
        # 0.5 * lmax * (...)
        g.fill_node_inputs([h, l_max, sub1], mul3)

        # 0.5 * FL + 0.5 * FR
        g.fill_node_inputs([h, (flux_l, i)], mul1)
        g.fill_node_inputs([h, (flux_r, i)], mul2)
        g.fill_node_inputs([mul1, mul2], add1)

        g.fill_node_inputs([add1, mul3], sub2)

        g.add_edge((sub2, 0), g.get_internal_output(i))
        g.add_edge((sub2, 0), g.get_internal_output(i+unknowns))
    
    return g