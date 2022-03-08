import unittest
from compute_graph.DAG.graph import DAG_Message
from compute_graph.DAG.visualize import visualize_graph
from compute_graph.examples.Euler.proper_euler import *
from compute_graph.examples.Euler.euler import *
from compute_graph.examples.Euler.test_euler import *
from compute_graph.examples.General.general import volumeX_2D

class Test_Proper_Flux_X(unittest.TestCase):
    def test_1(self):
        g = proper_flux_x()
        input_data = [1.0, 2.0, 3.0, 4.0]
        full_input = input_data + [-10.0, -11.00, -12.0, -13.0, -14.0]
        expected_data = Test_Flux_X.flux_formula_x(input_data)

        result = g.eval(full_input)
        assert_float_array_equal(self, result, expected_data)

class Test_Proper_Flux_Y(unittest.TestCase):
    def test_1(self):
        g = proper_flux_y()
        input_data = [1.0, 2.0, 3.0, 4.0]
        full_input = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = Test_Flux_Y.flux_formula_y(input_data)

        result = g.eval(full_input)
        assert_float_array_equal(self, result, expected_data)

class Test_Proper_Eigen_X(unittest.TestCase):
    def test_1(self):
        g = proper_max_eigen_x()
        input_data = [8.0, 2.0, 3.0, 15.0]

        full_input = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = [Test_Eigen_X.eigen_formula_x(input_data)]

        result = g.eval(full_input)
        assert_float_array_equal(self, result, expected_data)

class Test_Proper_Eigen_Y(unittest.TestCase):
    def test_1(self):
        g = proper_max_eigen_y()
        input_data = [8.0, 2.0, 3.0, 15.0]

        full_input = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = [Test_Eigen_Y.eigen_formula_y(input_data)]

        result = g.eval(full_input)
        assert_float_array_equal(self, result, expected_data)

class Test_Source_Term(unittest.TestCase):
    def test_1(self):
        g = source_term()
        input_data = [8.0, 2.0, 3.0, 15.0]
        full_input = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = [0.0, 0.0,0.0, 0.0]

        result = g.eval(full_input)
        assert_float_array_equal(self, result, expected_data)


if __name__=="__main__":
    unittest.main()