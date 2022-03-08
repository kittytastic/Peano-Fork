import unittest
from compute_graph.DAG.graph import Graph
from compute_graph.DAG.transform import DAG_Flatten

class TestFlatten(unittest.TestCase):
    def test_1(self):
        tf = DAG_Flatten()
        g_top = Graph(1, 1, "top")
        g_bottom = Graph(2, 1, "bottom")

        g_bottom.add_edge(g_bottom.get_internal_input(0), g_bottom.get_internal_output(0))
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(0))
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(1))
        g_top.add_edge(g_bottom.get_external_output(0), g_top.get_internal_output(0))

        g_flat = tf.tf(g_top)
        
        _, sub_graph = g_flat.get_categoriesed_sub_nodes()
        self.assertEqual(len(sub_graph), 0)
    

if __name__=="__main__":
    unittest.main()