import unittest
from compute_graph.DAG import *

class TestGetSubNode(unittest.TestCase):
    def test_1(self):
        g = Graph(2, 1, "test")
        a = Add(2)
        g.add_edge(g.get_internal_input(0), (a,0))
        g.add_edge(g.get_internal_input(1), (a,1))
        g.add_edge((a,0), g.get_internal_output(0))

        excpected_subnode = {*g.input_interface, *g.output_interface, a}
        observed_subnode = g.get_sub_nodes()

        self.assertEqual(observed_subnode, excpected_subnode)
    
    def test_2(self):
        g_inner = Graph(1,1,"inner")
        g_inner.add_edge(g_inner.get_internal_input(0), g_inner.get_internal_output(0))
        
        g = Graph(2, 1, "test")
        a = Add(2)
        g.add_edge(g.get_internal_input(0), g_inner.get_external_input(0))
        g.add_edge(g_inner.get_external_output(0), (a,0))
        g.add_edge(g.get_internal_input(1), (a,1))
        g.add_edge((a,0), g.get_internal_output(0))

        excpected_subnode = {*g.input_interface, *g.output_interface, a, g_inner}
        observed_subnode = g.get_sub_nodes()

        self.assertEqual(observed_subnode, excpected_subnode)


class TestEvalOrder(unittest.TestCase):
    def test_1(self):
        g = Graph(2, 1, "test")
        a = Add(2)
        g.add_edge(g.get_internal_input(0), (a,0))
        g.add_edge(g.get_internal_input(1), (a,1))
        g.add_edge((a,0), g.get_internal_output(0))

        excpected_order = [g.input_interface[0], g.input_interface[1], a, g.output_interface[0]]
        observed_order = g.eval_order()

        self.assertEqual(excpected_order, observed_order)
    
    def test_2(self):
        g_inner = Graph(1,1,"inner")
        g_inner.add_edge(g_inner.get_internal_input(0), g_inner.get_internal_output(0))
        
        g = Graph(2, 1, "test")
        a = Add(2)
        g.add_edge(g.get_internal_input(0), g_inner.get_external_input(0))
        g.add_edge(g_inner.get_external_output(0), (a,0))
        g.add_edge(g.get_internal_input(1), (a,1))
        g.add_edge((a,0), g.get_internal_output(0))

        excpected_order = [g.input_interface[0], g.input_interface[1], g, a, g.output_interface[0]]
        observed_order = g.eval_order()

        self.assertEqual(excpected_order, observed_order)

if __name__ == "__main__":
    unittest.main()