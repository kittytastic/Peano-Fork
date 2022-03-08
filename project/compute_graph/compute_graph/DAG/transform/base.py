from typing import List, Optional
from abc import ABC, abstractmethod
import time
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
        if self.verbose:
                outS = f"Inital DAG: "
                stats = working_DAG.stats()
                outS += f" {stats[1]} graphs  {stats[0]} nodes"
                print(outS)
        
        for tf in self.transforms:
            start = time.time()
            working_DAG = tf.tf(working_DAG)
            end = time.time()
            if self.verbose:
                outS = f"({end-start:.2f}s) {tf.name}: "
                stats = working_DAG.stats()
                outS += f" {stats[1]} graphs  {stats[0]} nodes"
                print(outS)
            
        return working_DAG