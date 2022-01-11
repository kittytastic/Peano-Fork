from typing import Optional
from node import *
from local_types import GraphViz

class PassThroughNode(Node):
    def __init__(self, name:Optional[str] = None):
        self.name = name
        super().__init__(1, 1)
    
    def visualize(self, dot:GraphViz):
        dot.node(str(self.id), f"{str(self)}") # type:ignore
    
    def _eval(self, inputs: List[Any])->List[Any]:
        return [inputs[0]]

    def __repr__(self):
        if self.name:
            return f"{self.name}"
        else:
            return f"PT-{super().__repr__()}"