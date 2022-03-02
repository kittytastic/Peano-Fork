import math
from typing import Dict
import unittest
from compute_graph.examples.Euler import *
from compute_graph.examples.Euler_test_extra import *

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
    @staticmethod
    def flux_formula_x(Q:List[float])->List[float]:
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
    @staticmethod
    def flux_formula_y(Q:List[float])->List[float]:
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
    @staticmethod
    def eigen_formula_x(Q:List[float])->float:
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
    @staticmethod
    def eigen_formula_y(Q:List[float])->float:
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


class Test_Rusanov(unittest.TestCase):
    @staticmethod
    def rusanov(Q:List[float], flux:Callable[[List[float]], List[float]], max_eigen: Callable[[List[float]], float])->List[float]:
        QL = Q[:4]
        QR = Q[4:]
        f:list[float] = [0]*4

        fluxL = flux(QL)
        fluxR = flux(QR)
        
        lambdaMaxL = max_eigen(QL)
        lambdaMaxR = max_eigen(QR)
        lambdaMax = max(lambdaMaxL, lambdaMaxR)

        for i in range(4):
            f[i] = 0.5 * fluxL[i] + 0.5 * fluxR[i] - 0.5 * lambdaMax * (QR[i]-QL[i])
       
        return f

    def test_1(self):
        g = rusanov(max_eigen_x, flux_x)
        input_data = [8.0, 2.0, 3.0, 15.0, 9.0, 6.0, 7.0, 100.0]
        expected_data = self.rusanov(input_data, Test_Flux_X.flux_formula_x, Test_Eigen_X.eigen_formula_x)

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2(self):
        g = rusanov(max_eigen_x, flux_x)
        input_data = [7.0, 5.0, 8.0, 101.0, 9.0, 1.0, 4.0, 16.0]
        expected_data = self.rusanov(input_data, Test_Flux_X.flux_formula_x, Test_Eigen_X.eigen_formula_x)

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_3(self):
        g = rusanov(max_eigen_y, flux_y)
        input_data = [7.0, 5.0, 8.0, 101.0, 9.0, 1.0, 4.0, 16.0]
        expected_data = self.rusanov(input_data, Test_Flux_Y.flux_formula_y, Test_Eigen_Y.eigen_formula_y)

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)

class Test_PatchUpdate(unittest.TestCase):
    @staticmethod
    def pack_input(Qin: List[float], extras: Dict[str,float]):
        return Qin + [extras["t"], extras["dt"], extras["pos0"], extras["pos1"], extras["size0"], extras["size1"]]

    def xtest_1(self):
        make_rus_x:Callable[[str], Graph] = lambda x: rusanov(max_eigen_x, flux_x, friendly_name=x)
        make_rus_y:Callable[[str], Graph] = lambda x: rusanov(max_eigen_y, flux_y, friendly_name=x)
        g = patchUpdate(3, 2, 4, make_rus_x, make_rus_y)

        input_data = self.pack_input(patch_update_in_1, patch_update_extra_1)
        expected_data = patch_update_out_1

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)

class Test_AnalyticalPatchUpdate(unittest.TestCase):
    def test_1(self):
        input_data = Test_PatchUpdate.pack_input(patch_update_in_1, patch_update_extra_1)
        expected_data = patch_update_out_1

        result = analytical_patch_update(input_data, 3, 2, 4,
            lambda x: Test_Rusanov.rusanov(x, Test_Flux_X.flux_formula_x,Test_Eigen_X.eigen_formula_x),
            lambda x: Test_Rusanov.rusanov(x, Test_Flux_Y.flux_formula_y,Test_Eigen_Y.eigen_formula_y),
        ) 
        assert_float_array_equal(self, result, expected_data)
    
if __name__=="__main__":
    unittest.main()