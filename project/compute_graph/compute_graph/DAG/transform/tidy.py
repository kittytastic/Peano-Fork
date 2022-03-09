from typing import Optional, Set
from compute_graph.DAG.graph import InputInterface, OutputInterface
from compute_graph.DAG.transform.base import DAG_Transfrom
from compute_graph.DAG import Graph, OutPort, InPort


class DAG_RemovePassThrough(DAG_Transfrom):
    def __init__(self):
        super().__init__()
    
    def tf(self, in_DAG: Graph) -> Graph:
        subnode, _ = in_DAG.get_categoriesed_sub_nodes()
        edges = in_DAG.get_edges()
        inverse_edges = in_DAG.inverse_edges()

        subnode-=set(in_DAG.input_interface)
        subnode-=set(in_DAG.output_interface)

        for n in subnode:
            if isinstance(n, InputInterface) or isinstance(n, OutputInterface):
                node_ip = InPort((n,0))
                node_op = OutPort((n,0))
                before_op = inverse_edges[node_ip]
                after_ips:Set[InPort] =  edges[node_op] if node_op in edges else set()

                if node_op in edges:
                    edges.pop(node_op)
                edges[before_op].remove(node_ip)
                edges[before_op]=edges[before_op].union(after_ips)

                inverse_edges.pop(node_ip)
                for aip in after_ips:
                    inverse_edges[aip] = before_op
        
        in_DAG.set_edges(edges)        
        
        
        
        return in_DAG