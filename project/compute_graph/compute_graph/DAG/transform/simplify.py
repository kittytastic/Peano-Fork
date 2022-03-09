from typing import FrozenSet, List, Set, Tuple, Dict, Union
from compute_graph.DAG.node import DAG_Node
from compute_graph.DAG.ops import Add
from compute_graph.DAG.primitive_node import Constant, PassThroughNode
from compute_graph.DAG.transform.base import DAG_Transfrom
from compute_graph.DAG import Graph, OutPort, InPort
from math import isclose


class DAG_RemoveArithmeticNoOps(DAG_Transfrom):
    def __init__(self):
        super().__init__()
    
    def tf(self, in_DAG: Graph) -> Graph:
        in_DAG = self.remove_add0(in_DAG)      
        
        return in_DAG
    

    def remove_add0(self, in_DAG:Graph)->Graph:
        edges = in_DAG.get_edges()
        inverse_edges = in_DAG.inverse_edges()
        sub_node, _ = in_DAG.get_categoriesed_sub_nodes()
        const_zero  = set([n for n in sub_node if isinstance(n, Constant) and isclose(n.value, 0)])
        binary_add  = set([n for n in sub_node if isinstance(n, Add) and n.num_inputs==2])

        remove_pairs:List[Tuple[Constant, Add, int]] = [] 

        for cz in const_zero:
            for n, p in edges[OutPort((cz,0))]:
                if n in binary_add:
                    remove_pairs.append((cz, n, p)) # type: ignore

        for const, op, op_port in remove_pairs:
            data_port_num = 1 if op_port == 0 else 0
            pt = PassThroughNode()
            op_out = OutPort((op, 0))
            op_data_in = InPort((op, data_port_num))
            op_const_in = InPort((op, op_port))
            const_out = OutPort((const, 0))
            before_port = inverse_edges[op_data_in]
            after_ports:Set[InPort] = edges[op_out] if op_out in edges else set()

            edges[OutPort((pt, 0))] = after_ports
            edges[before_port].add(InPort((pt, 0)))
            edges[before_port].remove(op_data_in)
            if op_out in edges: edges.pop(op_out)
            edges[const_out].remove(op_const_in)
            if len(edges[const_out])==0: edges.pop(const_out)

            for ap in after_ports: inverse_edges[ap] = OutPort((pt, 0))
            inverse_edges[InPort((pt, 0))] = before_port
            inverse_edges.pop(op_data_in)
            inverse_edges.pop(op_const_in)
            
        in_DAG.set_edges(edges)
        return in_DAG

class DAG_RemoveDuplicatedArithmetic(DAG_Transfrom):
    def __init__(self):
        super().__init__()
    
    def tf(self, in_DAG: Graph) -> Graph:

        req_map: Dict[Union[Tuple[OutPort, ...], FrozenSet[OutPort]], DAG_Node]    = {} 

        

        return in_DAG