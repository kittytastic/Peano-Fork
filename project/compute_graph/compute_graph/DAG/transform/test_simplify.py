from typing import Tuple
import unittest
from compute_graph.DAG import Graph
from compute_graph.DAG.node import DAG_Node, InPort, OutPort
from compute_graph.DAG.ops import Add, Subtract
from compute_graph.DAG.primitive_node import Constant
from compute_graph.DAG.transform import DAG_Flatten
from compute_graph.DAG.transform.simplify import DAG_RemoveArithmeticNoOps, DAG_RemoveDuplicatedArithmetic
from compute_graph.DAG.visualize import visualize_graph # type: ignore





def basic_g_1()->Tuple[Graph, DAG_Node, DAG_Node]:
        g_bottom = Graph(1, 1, "bottom")
        
        c1 = Constant(0.0)
        add1 = Add(2)
        
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), c1], add1)
        g_bottom.add_edge((add1, 0), g_bottom.get_internal_output(0))

        return  g_bottom, c1, add1

def basic_g_2()->Tuple[Graph, DAG_Node, DAG_Node, DAG_Node]:
        g_bottom = Graph(1, 1, "bottom")
        
        c1 = Constant(0.0)
        add1 = Add(2)
        add2 = Add(2)
        
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), c1], add1)
        g_bottom.fill_node_inputs([add1, c1], add2)
        g_bottom.add_edge((add2, 0), g_bottom.get_internal_output(0))

        return  g_bottom, c1, add1, add2

def basic_g_3()->Tuple[Graph, DAG_Node, DAG_Node, DAG_Node]:
        g_bottom = Graph(2, 1, "bottom")
        
        add1 = Add(2)
        add2 = Add(2)
        add3 = Add(2)
        
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), g_bottom.get_internal_input(1)], add1)
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(1), g_bottom.get_internal_input(0)], add2)
        g_bottom.fill_node_inputs([add1, add2], add3)
        g_bottom.add_edge((add3, 0), g_bottom.get_internal_output(0))

        return  g_bottom, add1, add2, add3

def basic_g_4()->Tuple[Graph, DAG_Node, DAG_Node, DAG_Node]:
        g_bottom = Graph(2, 1, "bottom")
        
        c1 = Constant(2)
        c2 = Constant(3)
        add1 = Add(3)
        
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), c1, c2], add1)
        g_bottom.add_edge((add1, 0), g_bottom.get_internal_output(0))

        return  g_bottom, add1, c1, c2


def basic_g_5()->Tuple[Graph, DAG_Node, DAG_Node, DAG_Node]:
        g_bottom = Graph(2, 1, "bottom")
        
        add1 = Subtract()
        add2 = Subtract()
        add3 = Add(2)
        
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), g_bottom.get_internal_input(1)], add1)
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), g_bottom.get_internal_input(1)], add2)
        g_bottom.fill_node_inputs([add1, add2], add3)
        g_bottom.add_edge((add3, 0), g_bottom.get_internal_output(0))

        return  g_bottom, add1, add2, add3

def basic_g_6()->Tuple[Graph, DAG_Node, DAG_Node, DAG_Node, DAG_Node, DAG_Node]:
        g_bottom = Graph(2, 1, "bottom")
        
        add1 = Add(2)
        add2 = Add(2)
        add3 = Add(2)
        add4 = Add(2)
        add5 = Add(2)
        
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), g_bottom.get_internal_input(1)], add1)
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), g_bottom.get_internal_input(1)], add2)
        g_bottom.fill_node_inputs([add1, add2], add3)
        g_bottom.fill_node_inputs([add1, add2], add4)
        g_bottom.fill_node_inputs([add3, add4], add5)
        g_bottom.add_edge((add5, 0), g_bottom.get_internal_output(0))

        return  g_bottom, add1, add2, add3, add4, add5
 #  visualize_graph(g_flat, out_path="../../Artifacts", out_file_name="before")

def basic_g_7()->Tuple[Graph, DAG_Node, DAG_Node, DAG_Node]:
        g_bottom = Graph(1, 1, "bottom")
        
        add1 = Add(2)
        add2 = Add(2)
        add3 = Add(2)
        
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), g_bottom.get_internal_input(0)], add1)
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), g_bottom.get_internal_input(0)], add2)
        g_bottom.fill_node_inputs([add1, add2], add3)
        g_bottom.add_edge((add3, 0), g_bottom.get_internal_output(0))

        return  g_bottom, add1, add2, add3
class TestRemoveArithmeticNoOp(unittest.TestCase):
    def xtest_1(self):
        tf = DAG_RemoveArithmeticNoOps()
        g, c1, add1 = basic_g_1()
        
        g_clean = tf.tf(g)
        sub_n, _ = g_clean.get_categoriesed_sub_nodes()

        self.assertNotIn(c1, sub_n) 
        self.assertNotIn(add1, sub_n) 
        for og in g.input_interface+g.input_interface: self.assertIn(og, sub_n)
    
    def test_1(self):
        tf = DAG_RemoveArithmeticNoOps()
        g, c1, add1, add2 = basic_g_2()
        
        g_clean = tf.tf(g)
        sub_n, _ = g_clean.get_categoriesed_sub_nodes()

        self.assertNotIn(c1, sub_n) 
        self.assertNotIn(add1, sub_n) 
        self.assertNotIn(add2, sub_n) 
        for og in g.input_interface+g.input_interface: self.assertIn(og, sub_n)
        
class TestRemoveDuplicatedArithmetic(unittest.TestCase):
    def test_1_comm(self):
        tf = DAG_RemoveDuplicatedArithmetic()
        g, add1, add2, add3 = basic_g_3()
        
        g_tf = tf.tf(g)
        
        sub_n, _ = g_tf.get_categoriesed_sub_nodes()

        self.assertNotIn(add2, sub_n) 
        self.assertIn(add1, sub_n) 
        self.assertIn(add3, sub_n) 
        for og in g.input_interface+g.input_interface: self.assertIn(og, sub_n)
    
    def test_2_const(self):
        tf = DAG_RemoveDuplicatedArithmetic()
        g, add1, c1, c2 = basic_g_4()
        
        g_tf = tf.tf(g)
        
        sub_n, _ = g_tf.get_categoriesed_sub_nodes()

        self.assertIn(add1, sub_n) 
        self.assertIn(c1, sub_n) 
        self.assertIn(c2, sub_n) 
        for og in g.input_interface+g.input_interface: self.assertIn(og, sub_n)
    
    def test_3_non_comm(self):
        tf = DAG_RemoveDuplicatedArithmetic()
        g, sub1, sub2, add1 = basic_g_5()
        
        g_tf = tf.tf(g)
        
        sub_n, _ = g_tf.get_categoriesed_sub_nodes()

        self.assertNotIn(sub2, sub_n) 
        self.assertIn(add1, sub_n) 
        self.assertIn(sub1, sub_n) 
        for og in g.input_interface+g.input_interface: self.assertIn(og, sub_n)
    
    def test_4_2_level(self):
        tf = DAG_RemoveDuplicatedArithmetic()
        g, add1, add2, add3, add4, add5 = basic_g_6()
        
        g_tf = tf.tf(g)
        
        sub_n, _ = g_tf.get_categoriesed_sub_nodes()

        self.assertNotIn(add2, sub_n) 
        self.assertNotIn(add4, sub_n) 
        self.assertIn(add1, sub_n) 
        self.assertIn(add3, sub_n) 
        self.assertIn(add5, sub_n) 
        for og in g.input_interface+g.input_interface: self.assertIn(og, sub_n)
    
    def test_5_dupe_deps(self):
        tf = DAG_RemoveDuplicatedArithmetic()
        g, add1, add2, add3 = basic_g_7()
        
        g_tf = tf.tf(g)
        
        sub_n, _ = g_tf.get_categoriesed_sub_nodes()

        self.assertNotIn(add2, sub_n) 
        self.assertIn(add1, sub_n) 
        self.assertIn(add3, sub_n) 
        for og in g.input_interface+g.input_interface: self.assertIn(og, sub_n)


if __name__=="__main__":
    unittest.main()