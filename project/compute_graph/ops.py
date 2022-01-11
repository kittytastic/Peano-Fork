from node import *
from local_types import GraphViz

class Add(Node):
    def __init__(self, num_inputs: int):
        super().__init__(num_inputs, 1)

    def _eval(self, inputs: List[Any])->List[Any]:
        return [sum(inputs)]
    
    def visualize(self, dot: GraphViz):
        dot.node(str(self.id), f"+") # type:ignore

    def __repr__(self):
        return f"Add-{super().__repr__()}"
        
class Subtract(Node):
    def __init__(self,):
        super().__init__(2, 1)

    def _eval(self, inputs: List[Any])->List[Any]:
        return [inputs[0]-inputs[1]]
    
    def visualize(self, dot: GraphViz):
        dot.node(str(self.id), f"-") # type:ignore

    def __repr__(self):
        return f"Sub-{super().__repr__()}"

class Multiply(Node):
    def __init__(self, num_inputs:int):
        super().__init__(num_inputs, 1)

    def _eval(self, inputs: List[Any])->List[Any]:
        total = 1
        for i in inputs:
            total *= i
        return [total]
    
    def visualize(self, dot: GraphViz):
        dot.node(str(self.id), f"*") # type:ignore

    def __repr__(self):
        return f"Sub-{super().__repr__()}"

