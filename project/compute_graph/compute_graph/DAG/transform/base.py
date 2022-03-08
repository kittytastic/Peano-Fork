from typing import List, Optional
from abc import ABC, abstractmethod
from compute_graph.DAG import Graph


class DAG_Transfrom(ABC):
    def __init__(self, name:Optional[str] = None):
        self.name = type(self).__name__ if name is None else name

    @abstractmethod
    def tf(self, in_DAG: Graph)->Graph:
        pass

class DAG_TransformChain(DAG_Transfrom):
    def __init__(self, transforms:List[DAG_Transfrom], verbose:bool=False) -> None:
        self.transforms = transforms
        self.verbose = verbose


    def tf(self, in_DAG: Graph) -> Graph:
        working_DAG = in_DAG
        for tf in self.transforms:
            working_DAG = tf.tf(working_DAG)
            if self.verbose:
                print(f"---------- tf {type(tf).__name__} -----------")
                print(working_DAG)
                print()
            
        return working_DAG