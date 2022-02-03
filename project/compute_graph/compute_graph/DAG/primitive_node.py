from typing import Optional
from compute_graph.DAG.node import *

class PassThroughNode(DAG_Node):
    def __init__(self, friendly_name:Optional[str] = None, type_name:Optional[str]=None):
        type_name_req = "PT" if not type_name else type_name
        super().__init__(1, 1, friendly_name=friendly_name, type_name=type_name_req)
    
    def _eval(self, inputs: List[Any])->List[Any]:
        return [inputs[0]]
    

class GraphInterface(PassThroughNode):
    def __init__(self, idx:int, parent_graph: DAG_Node, type_name:str, friendly_name:Optional[str]):
        self.idx = idx
        self.parent_graph = parent_graph
        super().__init__(friendly_name=friendly_name, type_name=type_name)

class InputInterface(GraphInterface):
    def __init__(self, idx:int, parent_graph: DAG_Node, friendly_name:Optional[str] = None):
        super().__init__(idx, parent_graph, "input", friendly_name=friendly_name)

class OutputInterface(GraphInterface):
    def __init__(self, idx:int, parent_graph:DAG_Node, friendly_name:Optional[str] = None):
        super().__init__(idx, parent_graph, "output", friendly_name=friendly_name)

class TerminalInput(DAG_Node):
    def __init__(self):
        super().__init__(1, 1, type_name="terminal")
    
    def _eval(self, inputs: List[Any])->List[Any]:
        raise Exception("Not implemented")
    