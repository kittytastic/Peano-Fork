from typing import Dict
import unittest
from compute_graph.DAG.graph import DAG_Message
from compute_graph.examples.Euler.proper_euler import *
from compute_graph.examples.Euler.test_euler import Test_Rusanov, Test_Flux_X, Test_Eigen_X, assert_float_array_equal
from compute_graph.examples.General.general import *
from compute_graph.examples.Euler.euler_test_extra import *

def return_val_graph(inputs:int, outputs:List[int])->Graph:
    g = Graph(inputs, len(outputs), "return val")
    ips:List[OutPort] = []
    for i in range(inputs):
        pt =PassThroughNode(f"Input {i}")
        g.add_edge(g.get_internal_input(i), (pt,0))
        ips.append(OutPort((pt, 0)))

    for idx, o in enumerate(outputs):
        g.add_edge(ips[o], g.get_internal_output(idx))
    
    return g

def zero_graph(inputs: int, outputs: int)->Graph:
    g = Graph(inputs, outputs, "zeros")
    zero = Constant(0)
    for idx in range(outputs):
        g.add_edge((zero, 0), g.get_internal_output(idx))
    
    return g

class Test_Proper_Rusanov(unittest.TestCase):
    def test_1(self):
        g = rusanov(4, 0, 2, proper_max_eigen_x, proper_flux_x, None)
        input_data = [8.0, 2.0, 3.0, 15.0, 9.0, 6.0, 7.0, 100.0]
        full_input = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = Test_Rusanov.rusanov(input_data, Test_Flux_X.flux_formula_x, Test_Eigen_X.eigen_formula_x)
        expected_data+=expected_data

        result = g.eval(full_input)
        assert_float_array_equal(self, result, expected_data)
    
    def test_2_ncp(self):
        g = rusanov(1, 1, 2, lambda :zero_graph(2+5,1), None, lambda: return_val_graph(4+5, [0]))
        input_data = [4.0, 5.0, 10.0, 11.0]
        full_input = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = [3.5, -3.5]


        g.assert_valid()
        result = g.eval(full_input)
        assert_float_array_equal(self, result, expected_data)
    
    def test_3_ncp(self):
        g = rusanov(1, 1, 2, lambda :zero_graph(2+5,1), None, lambda: return_val_graph(4+5, [3]))
        input_data = [4.0, 5.0, 10.0, 12.0]
        full_input = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = [3.5, -3.5]


        g.assert_valid()
        result = g.eval(full_input)
        assert_float_array_equal(self, result, expected_data)
    
    def test_4_flux(self):
        g = rusanov(1, 1, 2, lambda :zero_graph(2+5,1), lambda: return_val_graph(2+5, [0]), None)
        input_data = [4.0, 5.0, 10.0, 12.0]
        full_input = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = [7.0, 7.0]


        g.assert_valid()
        result = g.eval(full_input)
        assert_float_array_equal(self, result, expected_data)
    
    def test_5_eigen(self):
        g = rusanov(1, 1, 2,  lambda: return_val_graph(2+5, [0]), lambda :zero_graph(2+5,1), None)
        input_data = [4.0, 5.0, 10.0, 12.0]
        full_input = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = [-30.0, -30.0]


        g.assert_valid()
        result = g.eval(full_input)
        assert_float_array_equal(self, result, expected_data)
    
    def test_6_all(self):
        g = rusanov(1, 1, 2, lambda: return_val_graph(2+5, [0]), lambda: return_val_graph(2+5, [0]), lambda: return_val_graph(4+5, [3]))
        input_data = [4.0, 5.0, 10.0, 12.0]
        full_input = input_data + [-10.0, -11.0, -12.0, -13.0, -14.0]
        expected_data = [-30.0+7.0+3.5, -30.0+7.0-3.5]


        g.assert_valid()
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
        make_rus_x:Callable[[str], Graph] = lambda x: rusanov(4,0, 2, proper_max_eigen_x, proper_flux_x, None, friendly_name=x)
        make_rus_y:Callable[[str], Graph] = lambda x: rusanov(4,0, 2, proper_max_eigen_y, proper_flux_y, None, friendly_name=x)
        g = patchUpdate_2D(3, 4, 0, make_rus_x, make_rus_y, source_term)

        input_data = self.pack_input(patch_update_in_1, patch_update_extra_1)
        expected_data = patch_update_out_1


        result = g.eval(input_data)
        assert_float_array_equal(self, result, expected_data)
    
if __name__ == "__main__":
    unittest.main()