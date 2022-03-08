from typing import Callable
import unittest
from compute_graph.DAG.graph import DAG_Message, Graph
from compute_graph.DAG.ops import Multiply, Max, Subtract, Add
from compute_graph.DAG.primitive_node import Constant
from compute_graph.DAG.transform import DAG_Flatten
from compute_graph.DAG.visualize import visualize_graph

class TestFlatten(unittest.TestCase):
    def test_1(self):
        print("Hello")
        tf = DAG_Flatten()
        g_top = Graph(1, 1, "top")
        g_bottom = Graph(2, 1, "bottom")

        g_bottom.add_edge(g_bottom.get_internal_input(0), g_bottom.get_internal_output(0))
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(0))
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(1))
        g_top.add_edge(g_bottom.get_external_output(0), g_top.get_internal_output(0))

        
        visualize_graph(g_top, out_path="../Artifacts", out_file_name="test_before_flat")
        visualize_graph(g_top, out_path="../Artifacts", out_file_name="test_before", max_depth=1)

        g_flat = tf.tf(g_top)

        visualize_graph(g_flat, out_path="../Artifacts", out_file_name="test_after")
        
        _, sub_graph = g_flat.get_categoriesed_sub_nodes()
        self.assertEqual(len(sub_graph), 0)
    

if __name__=="__main__":
    unittest.main()