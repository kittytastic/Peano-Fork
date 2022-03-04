import math
from typing import List, Any, Optional

from compute_graph.DAG.node import DAG_Node

class Add(DAG_Node):
    def __init__(self, num_inputs: int, friendly_name:Optional[str]=None):
        super().__init__(num_inputs, 1, type_name="Add", friendly_name=friendly_name)

    def _eval(self, inputs: List[Any])->List[Any]:
        return [sum(inputs)]
    
        
class Subtract(DAG_Node):
    def __init__(self,  friendly_name:Optional[str]=None):
        super().__init__(2, 1, type_name="Sub", friendly_name=friendly_name)

    def _eval(self, inputs: List[Any])->List[Any]:
        return [inputs[0]-inputs[1]]
    

class Multiply(DAG_Node):
    def __init__(self, num_inputs:int, friendly_name:Optional[str]=None):
        super().__init__(num_inputs, 1, type_name="Mul", friendly_name=friendly_name)

    def _eval(self, inputs: List[Any])->List[Any]:
        total = 1
        for i in inputs:
            total *= i
        return [total]


class Divide(DAG_Node):
    def __init__(self,  friendly_name:Optional[str]=None):
        super().__init__(2, 1, type_name="Div", friendly_name=friendly_name)

    def _eval(self, inputs: List[Any])->List[Any]:
        return [inputs[0]/inputs[1]]

class Max(DAG_Node):
    def __init__(self,  arg_no:int, friendly_name:Optional[str]=None):
        super().__init__(arg_no, 1, type_name="Max", friendly_name=friendly_name)

    def _eval(self, inputs: List[Any])->List[Any]:
        return [max(inputs)]

class Sqrt(DAG_Node):
    def __init__(self, friendly_name:Optional[str]=None):
        super().__init__(1, 1, type_name="Sqrt", friendly_name=friendly_name)

    def _eval(self, inputs: List[Any])->List[Any]:
        return [math.sqrt(inputs[0])]

class Abs(DAG_Node):
    def __init__(self, friendly_name:Optional[str]=None):
        super().__init__(1, 1, type_name="Abs", friendly_name=friendly_name)

    def _eval(self, inputs: List[Any])->List[Any]:
        return [abs(inputs[0])]
