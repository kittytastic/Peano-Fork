from typing import Dict, Set
from compute_graph.DAG.graph import InputInterface, OutputInterface
from compute_graph.DAG.node import DAG_Node
from compute_graph.DAG.primitive_node import PassThroughNode
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
            if isinstance(n, InputInterface) or isinstance(n, OutputInterface) or isinstance(n, PassThroughNode):
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

class DAG_RemoveUnusedComp(DAG_Transfrom):
    def __init__(self):
        super().__init__()
    
    def tf(self, in_DAG: Graph) -> Graph:
        subnode, _ = in_DAG.get_categoriesed_sub_nodes()
        edges = in_DAG.get_edges()

        subnode-=set(in_DAG.input_interface)
        subnode-=set(in_DAG.output_interface)

        unused_nodes = self._get_unused_nodes(in_DAG)
        while len(unused_nodes)>0:
            inverse_edges = in_DAG.inverse_edges()
            edges = in_DAG.get_edges()

            for un in unused_nodes:
                
                for idx in range(un.num_outputs):
                    if (un, idx) in edges:
                        edges.pop(OutPort((un, idx)))

                for idx in range(un.num_inputs):
                    node_inport = InPort((un, idx))
                    before_port = inverse_edges[node_inport]
                    edges[before_port].remove(node_inport)
            

            in_DAG.set_edges(edges)
            unused_nodes = self._get_unused_nodes(in_DAG)
        

        
        return in_DAG

    def _get_unused_nodes(self, in_DAG: Graph)->Set[DAG_Node]:
        subnode, _ = in_DAG.get_categoriesed_sub_nodes()
        edges = in_DAG.get_edges()

        subnode-=set(in_DAG.input_interface)
        subnode-=set(in_DAG.output_interface)

        used_ports:Dict[DAG_Node, Set[int]] = {n:set() for n in subnode}

        for np, ips in edges.items():
            n, port = np
            if n in used_ports and len(ips)>0:
                used_ports[n].add(port)

        unused_nodes = set([n for n, ports in used_ports.items() if len(ports)==0])
        return unused_nodes