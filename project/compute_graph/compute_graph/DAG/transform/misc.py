from typing import Optional

from compute_graph.DAG import Graph
from compute_graph.DAG.transform.base import DAG_Transfrom
from compute_graph.DAG.visualize import visualize_graph


class DAG_Viz(DAG_Transfrom):
    def __init__(self, file_name:str = "tmp", max_depth:Optional[int] = None, out_dir:str="../../Artifacts", format:str="png"):
        super().__init__()
        self.file_name =  file_name
        self.max_depth = max_depth
        self.out_dir = out_dir
        self.format = format
    
    def tf(self, in_DAG: Graph) -> Graph:
        visualize_graph(in_DAG, out_path=self.out_dir, out_file_name=self.file_name, max_depth=self.max_depth, format=self.format)
        return in_DAG