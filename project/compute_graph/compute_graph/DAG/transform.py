from typing import List, Optional, Dict
from abc import ABC, abstractmethod
from compute_graph.DAG import Graph
from compute_graph.DAG.node import DAG_Node, InPort, OutPort
from compute_graph.DAG.visualize import visualize_graph


class DAG_Transfrom(ABC):
    def __init__(self):
        pass

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


class DAG_Flatten(DAG_Transfrom):
    def __init__(self, max_depth:Optional[int]=None):
        self.max_depth = max_depth
    
    def tf(self, in_DAG: Graph) -> Graph:
        #print(f"Flattening: {in_DAG}")
        return self._flatten(in_DAG, self.max_depth)


    def _flatten(self, in_DAG: Graph, max_depth: Optional[int]) -> Graph:
        if isinstance(max_depth, int) and max_depth==0:
            return in_DAG

        next_depth = max_depth-1 if max_depth is not None else max_depth

        _, sub_graph = in_DAG.get_categoriesed_sub_nodes()
        flat_sub_graphs = {sg: self._flatten(sg, next_depth) for sg in sub_graph}
        out_DAG = in_DAG
        for sg, fsg in flat_sub_graphs.items():
            #print(f"Flattening sub-graph: {sg}")
            out_DAG = self._replace_sub_graph(out_DAG, sg, fsg)
        return out_DAG

    def _replace_sub_graph(self, in_DAG: Graph, sub_g: Graph, flat_sub_g:Graph)->Graph:
        start_edges = in_DAG.get_edges()
        
        out_edges = [(n,p) for n,p in start_edges.keys() if n == sub_g]
        #print(f"Out Edges: {out_edges}")

        in_edges = {key:InPort((n, p)) for key, val in start_edges.items() for n, p in val if n==sub_g}
        #print(f"In Edges: {in_edges}")

        new_edges = {**start_edges, **flat_sub_g.get_edges()}
        
        for on, op in out_edges:
            new_edges[OutPort((flat_sub_g.output_interface[op], 0))] = new_edges[OutPort((on,op))]
            new_edges.pop(OutPort((on,op)))
        
        for key, val in in_edges.items():
            _, p = val
            new_edges[key].discard(val)
            new_edges[key].add(InPort((flat_sub_g.input_interface[p], 0)))

        in_DAG.set_edges(new_edges)
        return in_DAG

class DAG_Viz(DAG_Transfrom):
    def __init__(self, file_name:str = "tmp", max_depth:Optional[int] = None):
        self.file_name =  file_name
        self.max_depth = max_depth
    
    def tf(self, in_DAG: Graph) -> Graph:
        
        visualize_graph(in_DAG, out_path="../Artifacts", out_file_name=self.file_name, max_depth=self.max_depth, format="svg")
        return in_DAG