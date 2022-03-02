import math
import unittest
from compute_graph.examples.Euler import *

def assert_float_array_equal(obj: unittest.TestCase, a: List[float], b: List[float]):
    obj.assertEqual(len(a), len(b))

    for v_a, v_b in zip(a,b):
        obj.assertAlmostEqual(v_a, v_b)

class Test_irho(unittest.TestCase):
    def test_1(self):
        g = irho_graph()
        input_data = [3]
        expected_data = [1/3]

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)

    def test_2(self):
        g = irho_graph()
        input_data = [10]
        expected_data = [1/10]

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)

class Test_P(unittest.TestCase):
    def P_formula(self, Q:List[float]):
        irho = Q[0]
        return (1.4 - 1)*(Q[3] - 0.5* irho *(Q[1]*Q[1]+Q[2]*Q[2]))

    def test_1(self):
        g = p_graph()
        input_data = [1.0, 2.0, 3.0, 4.0]
        expected_data = [self.P_formula(input_data)]

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)

    def test_2(self):
        g = p_graph()
        input_data = [5.0, 6.0, 7.0, 8.0]
        expected_data = [self.P_formula(input_data)]

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)

class Test_Flux_X(unittest.TestCase):
    def flux_formula_x(self, Q:List[float])->List[float]:
        f:List[float] = [0]*4
        irho = 1/Q[0]
        p = (1.4-1) * (Q[3] - 0.5*irho*(Q[1]*Q[1]+Q[2]*Q[2]))

        f[0] = Q[1]
        f[1] = irho * Q[1] * Q[1] + p
        f[2] = irho * Q[1] * Q[2]
        f[3] = irho * Q[1] *(Q[3] + p)
        return f

    def test_1(self):
        g = flux_x()
        input_data = [1.0, 2.0, 3.0, 4.0]
        expected_data = self.flux_formula_x(input_data)

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2(self):
        g = flux_x()
        input_data = [5.0, 6.0, 7.0, 8.0]
        expected_data = self.flux_formula_x(input_data)

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)

class Test_Flux_Y(unittest.TestCase):
    def flux_formula_y(self, Q:List[float])->List[float]:
        f:List[float] = [0]*4
        irho = 1/Q[0]
        p = (1.4-1) * (Q[3] - 0.5*irho*(Q[1]*Q[1]+Q[2]*Q[2]))

        f[0] = Q[2]
        f[1] = irho * Q[2] * Q[1]
        f[2] = irho * Q[2] * Q[2] + p
        f[3] = irho * Q[2] *(Q[3] + p)
        return f

    def test_1(self):
        g = flux_y()
        input_data = [1.0, 2.0, 3.0, 4.0]
        expected_data = self.flux_formula_y(input_data)

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2(self):
        g = flux_y()
        input_data = [5.0, 6.0, 7.0, 8.0]
        expected_data = self.flux_formula_y(input_data)

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)

class Test_Eigen_X(unittest.TestCase):
    def eigen_formula_x(self, Q:List[float])->float:
        irho = 1/Q[0]
        p = (1.4-1) * (Q[3] - 0.5*irho*(Q[1]*Q[1]+Q[2]*Q[2]))

        c = math.sqrt(1.4*p*irho)
       
        return max(abs(Q[1] * irho - c), abs(Q[1] * irho + c))

    def test_1(self):
        g = max_eigen_x()
        input_data = [8.0, 2.0, 3.0, 15.0]
        expected_data = [self.eigen_formula_x(input_data)]

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2(self):
        g = max_eigen_x()
        input_data = [9.0, 6.0, 7.0, 100.0]
        expected_data = [self.eigen_formula_x(input_data)]

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)

class Test_Eigen_Y(unittest.TestCase):
    def eigen_formula_y(self, Q:List[float])->float:
        irho = 1/Q[0]
        p = (1.4-1) * (Q[3] - 0.5*irho*(Q[1]*Q[1]+Q[2]*Q[2]))

        c = math.sqrt(1.4*p*irho)
       
        return max(abs(Q[2] * irho - c), abs(Q[2] * irho + c))

    def test_1(self):
        g = max_eigen_y()
        input_data = [8.0, 2.0, 3.0, 15.0]
        expected_data = [self.eigen_formula_y(input_data)]

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2(self):
        g = max_eigen_y()
        input_data = [9.0, 6.0, 7.0, 100.0]
        expected_data = [self.eigen_formula_y(input_data)]

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)

if __name__=="__main__":
    unittest.main()