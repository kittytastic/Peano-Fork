import math
from typing import Dict
import unittest
from compute_graph.examples.Euler.Euler import *
from compute_graph.examples.Euler.Euler_test_extra import *

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
        g = rusanov_neat(max_eigen_x, flux_x)
        input_data = [8.0, 2.0, 3.0, 15.0, 9.0, 6.0, 7.0, 100.0]
        expected_data = self.rusanov(input_data, Test_Flux_X.flux_formula_x, Test_Eigen_X.eigen_formula_x)

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2(self):
        g = rusanov_neat(max_eigen_x, flux_x)
        input_data = [7.0, 5.0, 8.0, 101.0, 9.0, 1.0, 4.0, 16.0]
        expected_data = self.rusanov(input_data, Test_Flux_X.flux_formula_x, Test_Eigen_X.eigen_formula_x)

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_3(self):
        g = rusanov_neat(max_eigen_y, flux_y)
        input_data = [7.0, 5.0, 8.0, 101.0, 9.0, 1.0, 4.0, 16.0]
        expected_data = self.rusanov(input_data, Test_Flux_Y.flux_formula_y, Test_Eigen_Y.eigen_formula_y)

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)

class Test_PatchUpdate(unittest.TestCase):
    def mock_rusanov_1_unknown(self, name:str)->Graph:
        g = Graph(2,1, name)
        max1 = Max(2)
        div1 = Divide()
        c1 = Constant(2)
        g.fill_node_inputs([g.get_internal_input(0), g.get_internal_input(1)], max1)
        g.fill_node_inputs([max1, c1], div1)
        g.add_edge((div1,0), g.get_internal_output(0))
        return g

    @staticmethod
    def pack_input(Qin: List[float], extras: Dict[str,float]):
        return Qin + [extras["t"], extras["dt"], extras["pos0"], extras["pos1"], extras["size0"], extras["size1"]]

    def test_1(self):
        make_rus_x:Callable[[str], Graph] = lambda x: rusanov_neat(max_eigen_x, flux_x, friendly_name=x)
        make_rus_y:Callable[[str], Graph] = lambda x: rusanov_neat(max_eigen_y, flux_y, friendly_name=x)
        g = patchUpdate_neat(3, 2, 4, make_rus_x, make_rus_y)

        input_data = self.pack_input(patch_update_in_1, patch_update_extra_1)
        expected_data = patch_update_out_1

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)

    def test_mock_1(self):
        g = self.mock_rusanov_1_unknown("mock_rusanov")
        input_data = [7.0, 5.0]
        expected_data = [3.5]
        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_1_cell_1_unknown_1(self):
        g = patchUpdate_neat(1, 2, 1, self.mock_rusanov_1_unknown, self.mock_rusanov_1_unknown)

        dt,size, cells_per_patch = 0.1, 1.0, 1
        input_data = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0] + [0.0, dt, 0.0, 0.0, size, size]
        expected_data = [4 + (+2 +2 -2.5 -3.5)*dt /(size/cells_per_patch)]

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
    
    def test_1_cell_1d_1(self):
        dt = 0.1
        size = 1.0
        cells_per_patch = 1
        input_data = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0] + [0.0, dt, 0.0, 0.0, size, size]
        expected_data = [4 + (+2 +2 -2.5 -3.5)*dt /(size/cells_per_patch)]

        result = analytical_patch_update(input_data, cells_per_patch, 2, 1,
            lambda x: [max(x)/2],
            lambda x: [max(x)/2],
        ) 
        assert_float_array_equal(self, result, expected_data)
    
    def test_1_cell_1d_2(self):
        dt = 0.1
        size = 1.0
        cells_per_patch = 1
        input_data = [0.0, 8.0, 1.0, 7.0, 4.0, 6.0, 2.0, 5.0, 3.0] + [0.0, dt, 0.0, 0.0, size, size]
        expected_data = [4 + (+4 +3.5 -2.5 -3)*dt /(size/cells_per_patch)]

        result = analytical_patch_update(input_data, cells_per_patch, 2, 1,
            lambda x: [max(x)/2],
            lambda x: [max(x)/2],
        ) 
        assert_float_array_equal(self, result, expected_data)
    
    def test_1_cell_2d_1(self):
        dt = 0.1
        size = 1.0
        cells_per_patch = 1
        input_data = [i for j in zip([0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0], [0.0, 8.0, 1.0, 7.0, 4.0, 6.0, 2.0, 5.0, 3.0]) for i in j] + [0.0, dt, 0.0, 0.0, size, size]
        expected_data = [
            4 + (+2 +2 -2.5 -3.5)*dt /(size/cells_per_patch),
            4 + (+4 +3.5 -2.5 -3)*dt /(size/cells_per_patch)
            ]

        def mock_rusanov(Qin:List[float])->List[float]:
            Qout = [0.0]*(len(Qin)//2)
            for i in range(len(Qin)//2):
                Qout[i] = max(Qin[i], Qin[i+len(Qin)//2])/2
            return Qout

        result = analytical_patch_update(input_data, cells_per_patch, 2, 2,
            mock_rusanov,
            mock_rusanov,
        ) 
        assert_float_array_equal(self, result, expected_data)
    
    def test_4(self):
        dt = 0.1
        size = 2.0
        cells_per_patch = 2
        input_data = [float(i) for i in range(16)] + [0.0, dt, 0.0, 0.0, size, size]
        expected_data = [
            5 + (+2.5 +2.5 -3 -4.5)*dt /(size/cells_per_patch),
            6 + (+3 +3 -5 -3.5)*dt /(size/cells_per_patch),
            9 + (+4.5 +4.5 -6.5 -5)*dt /(size/cells_per_patch),
            10 + (+5 +5 -7 -5.5)*dt /(size/cells_per_patch),
            ]

        result = analytical_patch_update(input_data, cells_per_patch, 2, 1,
            lambda x: [max(x)/2],
            lambda x: [max(x)/2],
        ) 
        assert_float_array_equal(self, result, expected_data)
    
if __name__=="__main__":
    unittest.main()