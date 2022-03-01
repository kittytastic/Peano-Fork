import enum
from typing import Set, List, Any, Dict, Tuple, Optional, Union


from compute_graph.local_types import  ErrorMessage
from compute_graph.DAG.node import DAG_Node, GraphEdges, InPort, OutPort, NodePort
from compute_graph.DAG.helpers import assert_in_port_exists,  assert_out_port_exists
from compute_graph.DAG.primitive_node import PassThroughNode

class GraphInterface(PassThroughNode):
    def __init__(self, idx:int, parent_graph: 'Graph', type_name:str, friendly_name:Optional[str]):
        self.idx = idx
        self.parent_graph = parent_graph
        super().__init__(friendly_name=friendly_name, type_name=type_name)

class InputInterface(GraphInterface):
    def __init__(self, idx:int, parent_graph: 'Graph', friendly_name:Optional[str] = None):
        super().__init__(idx, parent_graph, "input", friendly_name=friendly_name)

class OutputInterface(GraphInterface):
    def __init__(self, idx:int, parent_graph: 'Graph', friendly_name:Optional[str] = None):
        super().__init__(idx, parent_graph, "output", friendly_name=friendly_name)

class Graph(DAG_Node):
    def __init__(self, inputs: int, outputs: int, friendly_name:str):
        super().__init__(inputs, outputs, friendly_name=friendly_name, type_name="Graph")
        self._edges: GraphEdges = {}
        self.input_interface = [InputInterface(i, self, friendly_name=f"input{i}") for i in range(inputs)]
        self.output_interface = [OutputInterface(i, self, friendly_name=f"output{i}") for i in range(outputs)]
        self.name = friendly_name

    def get_internal_input(self, idx:int)->OutPort:
        return OutPort((self.input_interface[idx], 0))
    
    def get_external_input(self, idx:int)->InPort:
        return InPort((self, idx))

    def get_internal_output(self, idx:int)->InPort:
        return InPort((self.output_interface[idx], 0))
    
    def get_external_output(self, idx:int)->OutPort:
        return OutPort((self, idx))

    def get_edges(self)->GraphEdges:
        return self._edges
    
    def set_edges(self, edges: GraphEdges):
        self._edges = edges

    def __getitem__(self, key:OutPort)->Set[InPort]:
        return self._edges[key]

    def __setitem__(self, key:OutPort, value:Set[InPort]):
        self._edges[key] = value

    def get_sub_nodes(self):
        sn, sg = self.get_categoriesed_sub_nodes()
        return sn.union(sg)

    def get_categoriesed_sub_nodes(self)->Tuple[Set[DAG_Node], Set['Graph']]:
        sub_nodes:set[DAG_Node] = set(self.input_interface)
        sub_nodes = sub_nodes.union(self.output_interface)

        all_sub_node = [n for n, _ in self._edges.keys()]
        for nps in self._edges.values():
            all_sub_node += [n for n,_ in nps]
            

        all_graphs = [g for g in all_sub_node if isinstance(g, Graph)]
        sub_graphs = set(all_graphs) 
        
        all_nodes = [n for n in all_sub_node if not isinstance(n, Graph)]
        sub_nodes = set(all_nodes)

        return sub_nodes, sub_graphs
       

    def validate(self) -> List[ErrorMessage]:
        sub_nodes = self.get_sub_nodes()
        require_full_input = sub_nodes - set(self.input_interface)

        ports_to_fullfill:Set[InPort] = set()
        for n in require_full_input:
            ports_to_fullfill.update([InPort((n, i)) for i in range(n.num_inputs)])

        ports_already_filled:Set[InPort] = set()
        errors:List[str] = []

        for set_op in self._edges.values():
            for in_port in set_op:
                if in_port in ports_already_filled:
                    errors.append(f"Port: {in_port} has already been used")


                if in_port not in ports_to_fullfill:
                    errors.append(f"Port: {in_port} filled in graph, but isn't in graph")
                 

                ports_to_fullfill.discard(in_port)
                ports_already_filled.add(in_port)

        
        if len(ports_to_fullfill)!=0:
            first_missing_ports:List[InPort] = list(ports_to_fullfill)[:min(len(ports_to_fullfill), 3)]
            errors.append(f"{len(ports_to_fullfill)} Unfilled ports: {','.join([str(p) for p in first_missing_ports])}")

        # TODO check for cycles
        # TODO check for unused outports

        return errors

    def add_edge(self, from_node:NodePort, to_node:NodePort):
        from_node = OutPort(from_node)
        to_node = InPort(to_node)
        assert_out_port_exists(from_node)
        assert_in_port_exists(to_node)

        if from_node in self._edges:
            self._edges[from_node].add(to_node)
        else:
            self._edges[from_node]={to_node}

    def fill_node_inputs(self, inputs: List[Union[NodePort, DAG_Node]], to_node:DAG_Node):
        assert(len(inputs)==to_node.num_inputs)
        for idx, port in enumerate(inputs):
            if isinstance(port, DAG_Node):
                assert(port.num_outputs==1)
                self.add_edge((port,0), (to_node, idx)) 
            else:
                self.add_edge(port, (to_node, idx)) 

    def _eval(self, inputs: List[Any])->List[Any]:

        sub_nodes = self.get_sub_nodes()
        node_requirements:Dict[DAG_Node, Set[int]] = {n: set(range(n.num_inputs)) for n in sub_nodes if n not in self.input_interface} 
        port_input_data:Dict[InPort, Any] = {InPort((self.input_interface[i], 0)):inputs[i] for i in range(self.num_inputs)}
        port_output_data:Dict[OutPort, Any] = {}
        ready_nodes:Set[DAG_Node] =  set(self.input_interface)
        complete_nodes: Set[DAG_Node] = set()

        while len(ready_nodes)>0:
            next_node = next(iter(ready_nodes))
            ready_nodes.remove(next_node)
            complete_nodes.add(next_node)
            print("New iteration")
            print(f"Next node {next_node}")

            # compute node
            input_data = [port_input_data[InPort((next_node, i))] for i in range(next_node.num_inputs)]
            output = next_node.eval(input_data)

            # update port output
            for idx, data in enumerate(output):
                op = OutPort((next_node, idx))
                port_output_data[op] = data

                if op in self._edges:    
                    for dependent_port in self._edges[op]:
                        port_input_data[dependent_port] = data

                        d_node, d_port = dependent_port
                        node_requirements[d_node].remove(d_port)

            
            # update any satisfied nodes
            newly_satisfied_nodes = [n for n,v in node_requirements.items() if len(v)==0]
            for nsn in newly_satisfied_nodes:
                del node_requirements[nsn]

            ready_nodes.update(newly_satisfied_nodes)

        return [port_output_data[OutPort((on,0))] for on in self.output_interface]

    def eval_order(self)->List[DAG_Node]:
        sub_nodes = self.get_sub_nodes()
        node_requirements:Dict[DAG_Node, Set[int]] = {n: set(range(n.num_inputs)) for n in sub_nodes if n not in self.input_interface} 
        ready_nodes:Set[DAG_Node] =  set(self.input_interface)
        complete_nodes: Set[DAG_Node] = set()

        eval_order: List[DAG_Node] = []

        while len(ready_nodes)>0:
            next_node = next(iter(ready_nodes))
            ready_nodes.remove(next_node)
            complete_nodes.add(next_node)
            eval_order.append(next_node)

            # update port output
            for idx in range(next_node.num_outputs):
                op = OutPort((next_node, idx))
                if op in self._edges:    
                    for dependent_port in self._edges[op]:
                        d_node, d_port = dependent_port
                        node_requirements[d_node].remove(d_port)

            
            # update any satisfied nodes
            newly_satisfied_nodes = [n for n,v in node_requirements.items() if len(v)==0]
            for nsn in newly_satisfied_nodes:
                del node_requirements[nsn]

            ready_nodes.update(newly_satisfied_nodes)

        return eval_order


    def inverse_edges(self)->Dict[InPort, OutPort]:
        inverse_edges = {ip: op for op, ips in self._edges.items() for ip in ips}
        return inverse_edges


