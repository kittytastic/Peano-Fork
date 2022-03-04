from typing import Optional
from compute_graph.DAG.node import *

class PassThroughNode(DAG_Node):
    def __init__(self, friendly_name:Optional[str] = None, type_name:Optional[str]=None):
        type_name_req = "PT" if not type_name else type_name
        super().__init__(1, 1, friendly_name=friendly_name, type_name=type_name_req)
    
    def _eval(self, inputs: List[Any])->List[Any]:
        return [inputs[0]]
    

class TerminalInput(DAG_Node):
    def __init__(self):
        super().__init__(1, 1, type_name="terminal")
    
    def _eval(self, inputs: List[Any])->List[Any]:
        raise Exception("Not implemented")


class Constant(DAG_Node):
    def __init__(self, value:float):
        self.value = value
        super().__init__(0, 1, "constant", f"{value}")

    def _eval(self, inputs: List[Any])->List[Any]:
        return [self.value]

class DebugNode(DAG_Node):
    def __init__(self, child_node:DAG_Node):
        super().__init__(child_node.num_inputs, child_node.num_outputs, type_name=f"DEBUG-{child_node.type_name}", friendly_name=f"DEBUG-{child_node.friendly_name}")
        self.child_node = child_node

    def _eval(self, inputs: List[Any]) -> List[Any]:
        print(f"[{str(self)}] inputs: {inputs}")
        res = self.child_node.eval(inputs)
        print(f"[{str(self)}] output: {res}")
        return res

    