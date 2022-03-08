from typing import Optional
from compute_graph.DAG.transform.base import DAG_Transfrom
from compute_graph.DAG import Graph, OutPort, InPort


class DAG_Flatten(DAG_Transfrom):
    def __init__(self, max_depth:Optional[int]=None):
        super().__init__()
        self.max_depth = max_depth
    
    def tf(self, in_DAG: Graph) -> Graph:
        return self._flatten(in_DAG, self.max_depth)


    def _flatten(self, in_DAG: Graph, max_depth: Optional[int]) -> Graph:
        if isinstance(max_depth, int) and max_depth==0:
            return in_DAG

        next_depth = max_depth-1 if max_depth is not None else max_depth

        _, sub_graph = in_DAG.get_categoriesed_sub_nodes()
        flat_sub_graphs = {sg: self._flatten(sg, next_depth) for sg in sub_graph}
        out_DAG = in_DAG
        for sg, fsg in flat_sub_graphs.items():
            out_DAG = self._replace_sub_graph(out_DAG, sg, fsg)
        return out_DAG

    def _replace_sub_graph(self, in_DAG: Graph, sub_g: Graph, flat_sub_g:Graph)->Graph:
        start_edges = in_DAG.get_edges()
        
        out_edges = [(n,p) for n,p in start_edges.keys() if n == sub_g]

        in_edges = {InPort((n, p)):key for key, val in start_edges.items() for n, p in val if n==sub_g}

        new_edges = {**start_edges, **flat_sub_g.get_edges()}
        
        for on, op in out_edges:
            new_edges[OutPort((flat_sub_g.output_interface[op], 0))] = new_edges[OutPort((on,op))]
            new_edges.pop(OutPort((on,op)))
        
        for val, key in in_edges.items():
            _, p = val
            new_edges[key].discard(val)
            new_edges[key].add(InPort((flat_sub_g.input_interface[p], 0)))

        in_DAG.set_edges(new_edges)
        return in_DAG