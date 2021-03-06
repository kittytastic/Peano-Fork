
from typing import Any, Dict, List, NewType, Optional, Set, Tuple
from abc import ABC, abstractmethod

from compute_graph.errors import *
from compute_graph.local_types import ErrorMessage

NodePort = Tuple['DAG_Node', int]
OutPort = NewType('OutPort', NodePort)
InPort = NewType('InPort', NodePort)
GraphEdges = Dict[OutPort, Set[InPort]]

class DAG_Node(ABC):
    next_global_id = 0

    def __init__(self, num_inputs:int, num_outputs:int, type_name:str="unknown", friendly_name:Optional[str]=None, commutative:bool = False):
        self.id = DAG_Node.next_global_id
        DAG_Node.next_global_id +=1
        
        self.num_inputs = num_inputs
        self.num_outputs = num_outputs
        self.type_name = type_name
        self.friendly_name = friendly_name
        self.commutative = commutative  

    @abstractmethod
    def _eval(self, inputs:List[Any])->List[Any]:
        pass

    def eval(self, input_data:List[Any])->List[Any]:
        if len(input_data)!= self.num_inputs:
            raise BadEval(f"Node {str(self)} was given a bad number of eval inputs, expected: {self.num_inputs} but received: {len(input_data)}")

        outputs = self._eval(input_data)

        if len(outputs)!=self.num_outputs:
            raise BadEval(f"Node {str(self)} produced a bad number of outputs, expected: {self.num_outputs} but received: {len(outputs)}")

        return outputs

    
    def __hash__(self) -> int:
        return self.id

    def __str__(self)->str:
        return self.__repr__() 
    
    def __repr__(self) -> str:
        raw_name = f"<{self.type_name}-{self.id}-node>"
        return f"<{self.friendly_name} ({raw_name})>" if self.friendly_name else f"{raw_name}"