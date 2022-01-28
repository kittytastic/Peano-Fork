from typing import Optional
from compute_graph.DAG.node import *

class PassThroughNode(DAG_Node):
    def __init__(self, friendly_name:Optional[str] = None, type_name:Optional[str]=None):
        type_name_req = "PT" if not type_name else type_name
        super().__init__(1, 1, friendly_name=friendly_name, type_name=type_name_req)
    
    def _eval(self, inputs: List[Any])->List[Any]:
        return [inputs[0]]
    

class InputPassThrough(PassThroughNode):
    def __init__(self, idx:int, friendly_name:Optional[str] = None):
        self.idx = idx
        super().__init__(friendly_name=friendly_name, type_name="input")


class TerminalInput(DAG_Node):
    def __init__(self):
        super().__init__(1, 1, type_name="terminal")
    
    def _eval(self, inputs: List[Any])->List[Any]:
        raise Exception("Not implemented")
    