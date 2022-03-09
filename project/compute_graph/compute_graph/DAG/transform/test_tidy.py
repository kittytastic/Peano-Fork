from typing import Tuple
import unittest
from compute_graph.DAG import Graph
from compute_graph.DAG.node import DAG_Node, InPort, OutPort
from compute_graph.DAG.ops import Add
from compute_graph.DAG.transform import DAG_Flatten
from compute_graph.DAG.transform.tidy import DAG_RemovePassThrough, DAG_RemoveUnusedComp
from compute_graph.DAG.visualize import visualize_graph


def basic_g_1()->Tuple[Graph, Graph]:
        g_top = Graph(1, 1, "top")
        g_bottom = Graph(2, 1, "bottom")

        g_bottom.add_edge(g_bottom.get_internal_input(0), g_bottom.get_internal_output(0))
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(0))
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(1))
        g_top.add_edge(g_bottom.get_external_output(0), g_top.get_internal_output(0))

        return g_top, g_bottom

def basic_g_2()->Tuple[Graph, Graph]:
        g_top = Graph(1, 1, "top")
        g_bottom = Graph(2, 2, "bottom")

        g_bottom.add_edge(g_bottom.get_internal_input(0), g_bottom.get_internal_output(0))
        g_bottom.add_edge(g_bottom.get_internal_input(1), g_bottom.get_internal_output(1))
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(0))
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(1))
        g_top.add_edge(g_bottom.get_external_output(0), g_top.get_internal_output(0))

        return g_top, g_bottom


def basic_g_3()->Tuple[Graph, Graph, Tuple[DAG_Node, DAG_Node]]:
        g_top = Graph(1, 1, "top")
        g_bottom = Graph(2, 2, "bottom")
        add1 = Add(2)
        add2 = Add(2)
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), g_bottom.get_internal_input(1)], add1)
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), g_bottom.get_internal_input(1)], add2)
        g_bottom.add_edge((add1, 0), g_bottom.get_internal_output(0))
        g_bottom.add_edge((add2, 0), g_bottom.get_internal_output(1))
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(0))
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(1))
        g_top.add_edge(g_bottom.get_external_output(0), g_top.get_internal_output(0))

        return g_top, g_bottom, (add1, add2)
 #  visualize_graph(g_flat, out_path="../../Artifacts", out_file_name="before")

class TestRemovePassthrough(unittest.TestCase):
    def test_1(self):
        tf = DAG_Flatten()
        tf2 = DAG_RemovePassThrough()
        g_top, g_bottom = basic_g_1()
        
        g_flat = tf.tf(g_top)
        g_clean = tf2.tf(g_flat)

        sub_n, _ = g_clean.get_categoriesed_sub_nodes()
        edges = g_clean.get_edges()
        
        for pt in g_bottom.input_interface+g_bottom.input_interface: self.assertNotIn(pt, sub_n)
        for og in g_top.input_interface+g_top.input_interface: self.assertIn(og, sub_n)
        
        self.assertIn(OutPort((g_top.input_interface[0],0)), edges)
        self.assertIn(InPort((g_top.output_interface[0], 0)), edges[OutPort((g_top.input_interface[0],0))])

class TestRemoveUnusedComp(unittest.TestCase):
    def test_1(self):
        tf = DAG_Flatten()
        tf2 = DAG_RemoveUnusedComp()
        g_top, g_bottom = basic_g_1()
        g_flat = tf.tf(g_top)
        
        g_clean = tf2.tf(g_flat)

        sub_n, _ = g_clean.get_categoriesed_sub_nodes()
        
        self.assertNotIn(g_bottom.input_interface[1], sub_n)
        for og in g_top.input_interface+g_top.input_interface: self.assertIn(og, sub_n)
    
    def test_2(self):
        tf = DAG_Flatten()
        tf2 = DAG_RemoveUnusedComp()
        g_top, g_bottom = basic_g_2()
        g_flat = tf.tf(g_top)
        
        g_clean = tf2.tf(g_flat)

        sub_n, _ = g_clean.get_categoriesed_sub_nodes()
        
        self.assertNotIn(g_bottom.input_interface[1], sub_n)
        self.assertNotIn(g_bottom.output_interface[1], sub_n)
        for og in g_top.input_interface+g_top.input_interface: self.assertIn(og, sub_n)
    
    def test_3(self):
        tf = DAG_Flatten()
        tf2 = DAG_RemoveUnusedComp()
        g_top, g_bottom, add = basic_g_3()
        g_flat = tf.tf(g_top)
        
        g_clean = tf2.tf(g_flat)

        sub_n, _ = g_clean.get_categoriesed_sub_nodes()
        
        self.assertIn(g_bottom.input_interface[1], sub_n)
        self.assertIn(add[0], sub_n)
        for og in g_top.input_interface+g_top.input_interface: self.assertIn(og, sub_n)


        self.assertNotIn(g_bottom.output_interface[1], sub_n)
        self.assertNotIn(add[1], sub_n)
        

        
        

if __name__=="__main__":
    unittest.main()