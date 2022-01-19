from typing import Optional
from node import *
from local_types import GraphViz

class PassThroughNode(Node):
    def __init__(self, friendly_name:Optional[str] = None, type_name:Optional[str]=None):
        type_name_req = "PT" if not type_name else type_name
        super().__init__(1, 1, friendly_name=friendly_name, type_name=type_name_req)
    
    def visualize(self, dot:GraphViz):
        name = self.friendly_name if self.friendly_name else str(self)
        dot.node(str(self.id), f"{name}") # type:ignore
    
    def _eval(self, inputs: List[Any])->List[Any]:
        return [inputs[0]]
    
    def ast_visit(self, in_ports_ast: List[AST_Node]) -> List[AST_Node]:
        return in_ports_ast
