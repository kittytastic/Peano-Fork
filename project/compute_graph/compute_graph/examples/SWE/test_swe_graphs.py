import unittest
from compute_graph.examples.SWE.swe_graphs import *

def assert_float_array_equal(obj: unittest.TestCase, a: List[float], b: List[float]):
    obj.assertEqual(len(a), len(b))

    for v_a, v_b in zip(a,b):
        obj.assertAlmostEqual(v_a, v_b)

class Test_SWE_Flux_X(unittest.TestCase):
    @staticmethod
    def flux_formula_x(Q:List[float])->List[float]:
        f:List[float] = [0]*3
        ih = 1/Q[0]

        f[0] = Q[1]
        f[1] = ih * Q[1] * Q[1]
        f[2] = ih * Q[1] * Q[2]
        return f

    def test_1(self):
        g = swe_flux_x()
        input_data = [1.0, 2.0, 3.0, 4.0]
        extra_data = [-11.0, -12.0, -13.0, -14.0, -15.0]
        expected_data = self.flux_formula_x(input_data)

        g.assert_valid()
        result = g.eval(input_data+extra_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2(self):
        g = swe_flux_x()
        input_data = [5.0, 6.0, 7.0, 8.0]
        extra_data = [-11.0, -12.0, -13.0, -14.0, -15.0]
        expected_data = self.flux_formula_x(input_data)

        g.assert_valid()
        result = g.eval(input_data+extra_data)
        assert_float_array_equal(self, result, expected_data)

class Test_SWE_Flux_Y(unittest.TestCase):
    @staticmethod
    def flux_formula_y(Q:List[float])->List[float]:
        f:List[float] = [0]*3
        ih = 1/Q[0]

        f[0] = Q[2]
        f[1] = ih * Q[2] * Q[1]
        f[2] = ih * Q[2] * Q[2]
        return f

    def test_1(self):
        g = swe_flux_y()
        input_data = [1.0, 2.0, 3.0, 4.0]
        extra_data = [-11.0, -12.0, -13.0, -14.0, -15.0]
        expected_data = self.flux_formula_y(input_data)

        g.assert_valid()
        result = g.eval(input_data+extra_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2(self):
        g = swe_flux_y()
        input_data = [5.0, 6.0, 7.0, 8.0]
        extra_data = [-11.0, -12.0, -13.0, -14.0, -15.0]
        expected_data = self.flux_formula_y(input_data)

        g.assert_valid()
        result = g.eval(input_data+extra_data)
        assert_float_array_equal(self, result, expected_data)

if __name__ == "__main__":
    unittest.main()