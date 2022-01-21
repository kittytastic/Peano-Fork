from compute_graph.node import *
from compute_graph.local_types import GraphViz
from compute_graph.AST.ast_nodes_g import AST_Add, AST_Mul, AST_Sub

class Add(Node):
    def __init__(self, num_inputs: int, friendly_name:Optional[str]=None):
        super().__init__(num_inputs, 1, type_name="Add", friendly_name=friendly_name)

    def _eval(self, inputs: List[Any])->List[Any]:
        return [sum(inputs)]
    
    def visualize(self, dot: GraphViz):
        dot.node(str(self.id), f"+") # type:ignore
    
    def ast_visit(self, in_ports_ast: List[AST_Node]) -> List[AST_Node]:
        return [AST_Add(in_ports_ast[0], in_ports_ast[1])]
        
class Subtract(Node):
    def __init__(self,  friendly_name:Optional[str]=None):
        super().__init__(2, 1, type_name="Sub", friendly_name=friendly_name)

    def _eval(self, inputs: List[Any])->List[Any]:
        return [inputs[0]-inputs[1]]
    
    def visualize(self, dot: GraphViz):
        dot.node(str(self.id), f"-") # type:ignore
    
    def ast_visit(self, in_ports_ast: List[AST_Node]) -> List[AST_Node]:
        return [AST_Sub(in_ports_ast[0], in_ports_ast[1])]

class Multiply(Node):
    def __init__(self, num_inputs:int, friendly_name:Optional[str]=None):
        super().__init__(num_inputs, 1, type_name="Mul", friendly_name=friendly_name)

    def _eval(self, inputs: List[Any])->List[Any]:
        total = 1
        for i in inputs:
            total *= i
        return [total]
    
    def visualize(self, dot: GraphViz):
        dot.node(str(self.id), f"*") # type:ignore

    def ast_visit(self, in_ports_ast: List[AST_Node]) -> List[AST_Node]:
        return [AST_Mul(in_ports_ast[0], in_ports_ast[1])]


