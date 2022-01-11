
from typing import Any, Dict, List, NewType, Set, Tuple
from abc import ABC
from errors import *
from local_types import GraphViz

NodePort = Tuple['Node', int]
OutPort = NewType('OutPort', NodePort)
InPort = NewType('InPort', NodePort)
GraphEdges = Dict[OutPort, Set[InPort]]

class Node(ABC):
    next_global_id = 0

    def __init__(self, num_inputs:int, num_outputs:int):
        self.id = Node.next_global_id
        Node.next_global_id +=1
        
        self.num_inputs = num_inputs
        self.num_outputs = num_outputs        

    def visualize(self, dot:GraphViz)->None:
        raise MethodNotImplemented(f"Parent class: {self.__class__.__name__}")
 
    def eval(self, input_data:List[Any])->List[Any]:
        if len(input_data)!= self.num_inputs:
            raise BadEval(f"Node {str(self)} was given a bad number of eval inputs, expected: {self.num_inputs} but received: {len(input_data)}")

        outputs = self._eval(input_data)

        if len(outputs)!=self.num_outputs:
            raise BadEval(f"Node {str(self)} produced a bad number of outputs, expected: {self.num_outputs} but received: {len(outputs)}")

        return outputs
    
    def _eval(self, inputs:List[Any])->List[Any]:
        raise MethodNotImplemented(f"Parent class: {self.__class__.__name__}")
    
    def validate(self)->bool:
        raise MethodNotImplemented(f"Parent class: {self.__class__.__name__}")
    
    def __hash__(self) -> int:
        return self.id

    def __str__(self)->str:
        return self.__repr__() 
    
    def __repr__(self) -> str:
        return f"Node_{self.id}"