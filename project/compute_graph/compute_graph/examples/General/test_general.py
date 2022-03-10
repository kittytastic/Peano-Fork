from typing import Dict
import unittest
from compute_graph.DAG.graph import DAG_Message
from compute_graph.examples.Euler.proper_euler import *
from compute_graph.examples.Euler.test_euler import Test_Rusanov, Test_Flux_X, Test_Eigen_X, assert_float_array_equal
from compute_graph.examples.General.general import *
from compute_graph.examples.Euler.euler_test_extra import *

class Test_Proper_Rusanov(unittest.TestCase):
    def test_1(self):
        g = rusanov(4, proper_max_eigen_x, proper_flux_x, None)
        input_data = [8.0, 2.0, 3.0, 15.0, 9.0, 6.0, 7.0, 100.0]
        full_input = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = Test_Rusanov.rusanov(input_data, Test_Flux_X.flux_formula_x, Test_Eigen_X.eigen_formula_x)
        expected_data+=expected_data

        result = g.eval(full_input)
        assert_float_array_equal(self, result, expected_data)

class Test_VolX(unittest.TestCase):
    @staticmethod
    def volX(inputs:List[float], axis:str)->List[float]:
        assert(axis=="x" or axis=="y")
        assert(len(inputs)==7)
        pc_x, pc_y, ps_x, ps_y, volH, x, y = inputs
        out_x, out_y = 0.0, 0.0

        out_x = pc_x - 0.5 * ps_x
        out_y = pc_y - 0.5 * ps_y

        if axis == "x":
            out_x += x * volH
            out_y += (y+0.5) * volH
        else:
            out_x += (x+0.5) * volH
            out_y += y * volH

        return [out_x, out_y]

    def test_1(self):
        axis = "x"
        g = volumeX_2D(axis)
        input_data = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0]
        expected_data = self.volX(input_data, axis)

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2(self):
        axis = "y"
        g = volumeX_2D(axis)
        input_data = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0]
        expected_data = self.volX(input_data, axis)

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)


class TestPatchUpdate2D(unittest.TestCase):
    @staticmethod
    def pack_input(Qin: List[float], extras: Dict[str,float]):
        return Qin + [extras["t"], extras["dt"], extras["pos0"], extras["pos1"], extras["size0"], extras["size1"]]

    def test_1(self):
        make_rus_x:Callable[[str], Graph] = lambda x: rusanov(4, proper_max_eigen_x, proper_flux_x, None, friendly_name=x)
        make_rus_y:Callable[[str], Graph] = lambda x: rusanov(4, proper_max_eigen_y, proper_flux_y, None, friendly_name=x)
        g = patchUpdate_2D(3, 4, make_rus_x, make_rus_y, source_term)

        input_data = self.pack_input(patch_update_in_1, patch_update_extra_1)
        expected_data = patch_update_out_1

        DAG_Message.print_summary(g.validate(), max_msg=0)

        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)
    
if __name__ == "__main__":
    unittest.main()