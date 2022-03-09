import unittest
from compute_graph.DAG import Graph
from compute_graph.DAG.node import InPort, OutPort
from compute_graph.DAG.transform import DAG_Flatten
from compute_graph.DAG.transform.tidy import DAG_RemovePassThrough
from compute_graph.DAG.visualize import visualize_graph

class TestRemovePassthrough(unittest.TestCase):
    def test_1(self):
        tf = DAG_Flatten()
        tf2 = DAG_RemovePassThrough()
        g_top = Graph(1, 1, "top")
        g_bottom = Graph(2, 1, "bottom")

        g_bottom.add_edge(g_bottom.get_internal_input(0), g_bottom.get_internal_output(0))
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(0))
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(1))
        g_top.add_edge(g_bottom.get_external_output(0), g_top.get_internal_output(0))

        g_flat = tf.tf(g_top)
        visualize_graph(g_flat, out_path="../../Artifacts", out_file_name="before")

        g_clean = tf2.tf(g_flat)
        visualize_graph(g_clean, out_path="../../Artifacts", out_file_name="after")


        sub_n, sub_g = g_clean.get_categoriesed_sub_nodes()
        
        self.assertNotIn(g_bottom, sub_g)
        for pt in g_bottom.input_interface+g_bottom.input_interface:
            self.assertNotIn(pt, sub_n)
        
        for og in g_top.input_interface+g_top.input_interface:
            self.assertIn(og, sub_n)
        
        edges = g_clean.get_edges()
        self.assertIn(OutPort((g_top.input_interface[0],0)), edges)
        self.assertIn(InPort((g_top.output_interface[0], 0)), edges[OutPort((g_top.input_interface[0],0))])
        

        
        

if __name__=="__main__":
    unittest.main()