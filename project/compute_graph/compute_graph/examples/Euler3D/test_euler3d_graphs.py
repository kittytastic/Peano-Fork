import math
from typing import List
import unittest
from compute_graph.DAG.graph import DAG_Message
from compute_graph.examples.Euler3D.euler3d_graphs import *

def assert_float_array_equal(obj: unittest.TestCase, a: List[float], b: List[float]):
    obj.assertEqual(len(a), len(b))

    for v_a, v_b in zip(a,b):
        obj.assertAlmostEqual(v_a, v_b)


class Test_P(unittest.TestCase):
    @staticmethod
    def p(Q:List[float])->List[float]:
        irho = Q[0]
        p = (1.4-1) * (Q[4] - 0.5*irho*(Q[1]*Q[1]+Q[2]*Q[2]+Q[3]*Q[3]))
        return [p]

    def test_1(self):
        g = p_graph()
        input_data = [1.0, 2.0, 3.0, 4.0, 5.0]
        full_data = input_data
        expected_data = self.p(input_data)

        g.assert_valid()
        result = g.eval(full_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2(self):
        g = p_graph()
        input_data = [5.0, 4.0, 3.0, 2.0, 1.0]
        full_data = input_data
        expected_data = self.p(input_data)

        g.assert_valid()
        result = g.eval(full_data)
        assert_float_array_equal(self, result, expected_data)

class Test_Flux_X(unittest.TestCase):
    @staticmethod
    def flux_formula_x(Q:List[float])->List[float]:
        f:List[float] = [0]*5
        irho = 1/Q[0]
        p = (1.4-1) * (Q[4] - 0.5*irho*(Q[1]*Q[1] + Q[2]*Q[2] + Q[3]*Q[3]))

        f[0] = Q[1]
        f[1] = irho * Q[1] * Q[1] + p
        f[2] = irho * Q[1] * Q[2]
        f[3] = irho * Q[1] * Q[3]
        f[4] = irho * Q[1] *(Q[4] + p)
        return f

    def test_1(self):
        g = flux_x()
        input_data = [1.0, 2.0, 3.0, 4.0, 5.0]
        full_data = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = self.flux_formula_x(input_data)

        g.assert_valid()
        result = g.eval(full_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2(self):
        g = flux_x()
        input_data = [5.0, 6.0, 7.0, 8.0, 9.0]
        full_data = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = self.flux_formula_x(input_data)

        g.assert_valid()
        result = g.eval(full_data)
        assert_float_array_equal(self, result, expected_data)

class Test_Flux_Y(unittest.TestCase):
    @staticmethod
    def flux_formula_y(Q:List[float])->List[float]:
        f:List[float] = [0]*5
        irho = 1/Q[0]
        p = (1.4-1) * (Q[4] - 0.5*irho*(Q[1]*Q[1] + Q[2]*Q[2] + Q[3]*Q[3]))

        f[0] = Q[2]
        f[1] = irho * Q[2] * Q[1] 
        f[2] = irho * Q[2] * Q[2] + p
        f[3] = irho * Q[2] * Q[3]
        f[4] = irho * Q[2] *(Q[4] + p)
        return f

    def test_1(self):
        g = flux_y()
        input_data = [1.0, 2.0, 3.0, 4.0, 5.0]
        full_data = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = self.flux_formula_y(input_data)

        g.assert_valid()
        result = g.eval(full_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2(self):
        g = flux_y()
        input_data = [5.0, 6.0, 7.0, 8.0, 9.0]
        full_data = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = self.flux_formula_y(input_data)

        g.assert_valid()
        result = g.eval(full_data)
        assert_float_array_equal(self, result, expected_data)

class Test_Flux_Z(unittest.TestCase):
    @staticmethod
    def flux_formula_z(Q:List[float])->List[float]:
        f:List[float] = [0]*5
        irho = 1/Q[0]
        p = (1.4-1) * (Q[4] - 0.5*irho*(Q[1]*Q[1] + Q[2]*Q[2] + Q[3]*Q[3]))

        f[0] = Q[3]
        f[1] = irho * Q[3] * Q[1] 
        f[2] = irho * Q[3] * Q[2]
        f[3] = irho * Q[3] * Q[3] + p
        f[4] = irho * Q[3] *(Q[4] + p)
        return f

    def test_1(self):
        g = flux_z()
        input_data = [1.0, 2.0, 3.0, 4.0, 5.0]
        full_data = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = self.flux_formula_z(input_data)

        g.assert_valid()
        result = g.eval(full_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2(self):
        g = flux_z()
        input_data = [5.0, 6.0, 7.0, 8.0, 9.0]
        full_data = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = self.flux_formula_z(input_data)

        g.assert_valid()
        result = g.eval(full_data)
        assert_float_array_equal(self, result, expected_data)


class Test_Eigen_X(unittest.TestCase):
    @staticmethod
    def eigen_formula_x(Q:List[float])->List[float]:
        irho = 1/Q[0]
        p = (1.4-1) * (Q[4] - 0.5*irho*(Q[1]*Q[1] + Q[2]*Q[2] + Q[3]*Q[3]))
        c = math.sqrt(1.4 * p* irho)
        
        return [max(abs(Q[1] * irho -c), abs(Q[1]* irho +c))]

    def test_1(self):
        g = max_eigen_x()
        input_data = [8.0, 2.0, 3.0, 4.0, 15.0]
        full_data = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = self.eigen_formula_x(input_data)

        g.assert_valid()
        result = g.eval(full_data)
        assert_float_array_equal(self, result, expected_data)

class Test_Eigen_Y(unittest.TestCase):
    @staticmethod
    def eigen_formula_y(Q:List[float])->List[float]:
        irho = 1/Q[0]
        p = (1.4-1) * (Q[4] - 0.5*irho*(Q[1]*Q[1] + Q[2]*Q[2] + Q[3]*Q[3]))
        c = math.sqrt(1.4 * p* irho)
        
        return [max(abs(Q[2] * irho -c), abs(Q[2]* irho +c))]

    def test_1(self):
        g = max_eigen_y()
        input_data = [8.0, 2.0, 3.0, 4.0, 15.0]
        full_data = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = self.eigen_formula_y(input_data)

        g.assert_valid()
        result = g.eval(full_data)
        assert_float_array_equal(self, result, expected_data)

class Test_Eigen_Z(unittest.TestCase):
    @staticmethod
    def eigen_formula_z(Q:List[float])->List[float]:
        irho = 1/Q[0]
        p = (1.4-1) * (Q[4] - 0.5*irho*(Q[1]*Q[1] + Q[2]*Q[2] + Q[3]*Q[3]))
        c = math.sqrt(1.4 * p* irho)
        
        return [max(abs(Q[3] * irho -c), abs(Q[3]* irho +c))]

    def test_1(self):
        g = max_eigen_z()
        input_data = [8.0, 2.0, 3.0, 4.0, 15.0]
        full_data = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = self.eigen_formula_z(input_data)

        g.assert_valid()
        result = g.eval(full_data)
        assert_float_array_equal(self, result, expected_data)

if __name__=="__main__":
    unittest.main()