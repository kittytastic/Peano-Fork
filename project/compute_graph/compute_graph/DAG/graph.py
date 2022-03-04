from enum import Enum
from typing import Set, List, Any, Dict, Tuple, Optional, Union


from compute_graph.DAG.node import DAG_Node, GraphEdges, InPort, OutPort, NodePort
from compute_graph.DAG.helpers import assert_in_port_exists,  assert_out_port_exists
from compute_graph.DAG.primitive_node import PassThroughNode

class DAG_MessageType(Enum):
    INFO = 0
    WARNING = 1
    ERROR = 2


class DAG_Message():
    def __init__(self, level:DAG_MessageType, stack_trace: List['Graph'], message:str) -> None:
        self.level = level
        self.stack_trace = stack_trace
        self.message = message

    def __str__(self):
        if self.level == DAG_MessageType.INFO: level="INFO"
        elif self.level == DAG_MessageType.WARNING: level="WARNING"
        else: level="ERROR"
        
        st = [str(g) for g in self.stack_trace]
        st = " > ".join(st)

        return f"[{level}] {self.message}     ({st})"

    @staticmethod
    def print_summary(messages: List['DAG_Message'], max_msg:Optional[int]=None, min_level:DAG_MessageType = DAG_MessageType.INFO, exit_if_error:bool=True):
        errors = [m for m in messages if m.level == DAG_MessageType.ERROR]
        warnings = [m for m in messages if m.level == DAG_MessageType.WARNING]
        info = [m for m in messages if m.level == DAG_MessageType.INFO]

        print_order = list(errors)
        if min_level==DAG_MessageType.WARNING or min_level==DAG_MessageType.INFO: print_order+=warnings 
        if min_level==DAG_MessageType.INFO: print_order+=info 

        print(f"Validate found: {len(errors)} errors  {len(warnings)} warnings  {len(info)} info  ({len(messages)} total)")
        max_print_count = len(messages) if max_msg is None else max_msg
        print_count = min(len(print_order), max_print_count)

        for i in range(print_count):
            print(str(print_order[i]))

        if exit_if_error and len(errors)>0:
            raise Exception(f"Graph Validate failed with {len(errors)} errors")

    @staticmethod
    def get_stats(messages: List['DAG_Message']):
        errors = [m for m in messages if m.level == DAG_MessageType.ERROR]
        warnings = [m for m in messages if m.level == DAG_MessageType.WARNING]
        info = [m for m in messages if m.level == DAG_MessageType.INFO]
    
        return (len(errors), len(warnings), len(info))

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
        interface_nodes:set[DAG_Node] = set(self.input_interface)
        interface_nodes = interface_nodes.union(self.output_interface)

        child_sub_nodes = [n for n, _ in self._edges.keys()]
        for nps in self._edges.values():
            child_sub_nodes += [n for n,_ in nps]
            
        all_sub_node = set(child_sub_nodes).union(interface_nodes)

        all_graphs = [g for g in all_sub_node if isinstance(g, Graph)]
        sub_graphs = set(all_graphs) 
        
        all_nodes = [n for n in all_sub_node if not isinstance(n, Graph)]
        sub_nodes = set(all_nodes)

        return sub_nodes, sub_graphs
       

    def validate(self) -> List[DAG_Message]:
        # TODO check for cycles
        return self._validate([])

    def _validate(self, parent_stack_trace: List['Graph'])->List[DAG_Message]:
        stack_trace = list(parent_stack_trace) + [self]
        msgs:List[DAG_Message] = []

        sub_nodes, sub_graph = self.get_categoriesed_sub_nodes()

        all_sub_nodes = sub_nodes.union(sub_graph)
        
        outport_tracker: Dict[OutPort, int] = {OutPort((n,i)): 0 for n in all_sub_nodes for i in range(n.num_outputs)}
        inport_tracker: Dict[InPort, Set[OutPort]] = {ip:set() for ip,_ in self.inverse_edges().items()}

        for op, ips in self._edges.items():
            if op not in outport_tracker:
                msgs.append(DAG_Message(DAG_MessageType.ERROR, stack_trace, f"Outport {op} is used in graph, but not a subnode?!"))
            else:
                outport_tracker[op] += len(self._edges[op])
            for ip in ips:
                inport_tracker[ip].add(op)

        for op, count in outport_tracker.items():
            if count == 0 and op[0] not in self.output_interface:
                msgs.append(DAG_Message(DAG_MessageType.INFO, stack_trace, f"Outport {op} is unused"))
        
        for ip, ops in inport_tracker.items():
            if len(ops) == 0 and ip[0] not in self.input_interface:
                msgs.append(DAG_Message(DAG_MessageType.ERROR, stack_trace, f"Inport {ip} has not been filled"))
            elif len(ops)>1:
                msgs.append(DAG_Message(DAG_MessageType.ERROR, stack_trace, f"Inport {ip} has {len(ops)} incoming connections. It can only have 1. {ops}"))




        for sg in sub_graph:
            msgs += sg._validate(stack_trace)
        
        return msgs



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


