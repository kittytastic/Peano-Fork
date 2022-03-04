import unittest
from compute_graph.examples.Euler.proper_euler import *
from compute_graph.examples.Euler.test_euler import Test_Rusanov, Test_Flux_X, Test_Eigen_X, assert_float_array_equal
from compute_graph.examples.General.general import *

class Test_Proper_Rusanov(unittest.TestCase):
    def test_1(self):
        g = rusanov(4, proper_max_eigen_x, proper_flux_x)
        input_data = [8.0, 2.0, 3.0, 15.0, 9.0, 6.0, 7.0, 100.0]
        full_input = input_data + [-10.0, -12.0, -13.0, -14.0]
        expected_data = Test_Rusanov.rusanov(input_data, Test_Flux_X.flux_formula_x, Test_Eigen_X.eigen_formula_x)
        expected_data+=expected_data

        result = g.eval(full_input)
        assert_float_array_equal(self, result, expected_data)

    
if __name__ == "__main__":
    unittest.main()