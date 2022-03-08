from typing import Callable
import unittest
from compute_graph.DAG.graph import Graph
from compute_graph.DAG.ops import Multiply, Max, Subtract, Add
from compute_graph.DAG.primitive_node import Constant
from compute_graph.DAG.transform import DAG_Flatten
from compute_graph.DAG.visualize import visualize_graph

class TestFlatten(unittest.TestCase):
    def xtest_1(self):
        tf = DAG_Flatten()
        g_top_top = Graph(2, 1, "top_top")
        g_top = Graph(2, 1, "top")
        g_bottom = Graph(2, 1, "bottom")

        g_bottom.add_edge(g_bottom.get_internal_input(0), g_bottom.get_internal_output(0))
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(0))
        g_top.add_edge(g_top.get_internal_input(1), g_bottom.get_external_input(1))
        g_top.add_edge(g_bottom.get_external_output(0), g_top.get_internal_output(0))

        g_top_top.add_edge(g_top_top.get_internal_input(0), g_top.get_external_input(0))
        g_top_top.add_edge(g_top_top.get_internal_input(1), g_top.get_external_input(1))
        g_top_top.add_edge(g_top.get_external_output(0), g_top_top.get_internal_output(0))
        
        visualize_graph(g_top_top, out_path="../Artifacts", out_file_name="test_before")

        g_flat = tf.tf(g_top_top)

        visualize_graph(g_flat, out_path="../Artifacts", out_file_name="test_after")
    
    def test_2(self):
        g = test_rusanov(4, proper_max_eigen_x, proper_flux_x)

        tf = DAG_Flatten()
        visualize_graph(g, out_path="../Artifacts", out_file_name="test_before")

        g_flat = tf.tf(g)

        visualize_graph(g_flat, out_path="../Artifacts", out_file_name="test_after")

        _, sub_graph = g_flat.get_categoriesed_sub_nodes()
        self.assertEqual(len(sub_graph), 0)
        

def test_rusanov(
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

def proper_flux_x()->Graph:
    g = Graph(4+2+1+1+1, 4, "proper-flux-x")
    for i in range(4):
        g.add_edge(g.get_internal_input(i), g.get_internal_output(i))
    return g

def proper_max_eigen_x()->Graph:
    g = Graph(4+2+1+1+1, 1, "proper-max-eigen-x")
    g.add_edge(g.get_internal_input(0), g.get_internal_output(0))
    
    return g

if __name__=="__main__":
    unittest.main()