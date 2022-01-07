from typing import Any, Dict, List, NewType, Optional, Set, Tuple
import graphviz # type: ignore
from abc import ABC
import os


class MethodNotImplemented(Exception):
    pass

class PortDoesntExist(Exception):
    pass

class BadEvalArgs(Exception):
    pass

class InvalidGraph(Exception):
    pass

NodePort = Tuple['Node', int]
OutPort = NewType('OutPort', NodePort)
InPort = NewType('InPort', NodePort)
GraphEdges = Dict[OutPort, Set[InPort]]

class Node(ABC):
    next_global_id = 0

    def __init__(self, num_inputs:int, num_outputs:int):
        self.id = Node.next_global_id
        Node.next_global_id +=1
        
        self.num_inputs = num_inputs
        self.num_outputs = num_outputs        

    def visualize(self, dot:graphviz.Digraph)->None:
        raise MethodNotImplemented(f"Parent class: {self.__class__.__name__}")
 
    def eval(self, input:List[Any])->List[Any]:
        raise MethodNotImplemented(f"Parent class: {self.__class__.__name__}")
    
    def validate(self)->bool:
        raise MethodNotImplemented(f"Parent class: {self.__class__.__name__}")
    
    def __hash__(self) -> int:
        return self.id

    def __str__(self)->str:
        return self.__repr__() 
    
    def __repr__(self) -> str:
        return f"Node_{self.id}"

class PassThroughNode(Node):
    def __init__(self):
        super().__init__(1, 1)
    
    def visualize(self, dot: graphviz.Digraph):
        dot.node(str(self.id), f"{self.id}") # type:ignore

    def __repr__(self):
        return f"PT-{super().__repr__()}"

class Graph(Node):
    def __init__(self, inputs: int, outputs: int):
        super().__init__(inputs, outputs)
        self._edges: GraphEdges = {}
        self.input_interface = [PassThroughNode() for _ in range(inputs)]
        self.output_interface = [PassThroughNode() for _ in range(outputs)]

    def get_internal_input(self, idx:int)->OutPort:
        return OutPort((self.input_interface[idx], 0))

    def get_internal_output(self, idx:int)->InPort:
        return InPort((self.output_interface[idx], 0))

    def __getitem__(self, key:OutPort)->Set[InPort]:
        return self._edges[key]

    def __setitem__(self, key:OutPort, value:Set[InPort]):
        self._edges[key] = value

    
    def _get_sub_nodes(self)->Set[Node]:
        sub_nodes:set[Node] = set(self.input_interface)
        sub_nodes = sub_nodes.union(self.output_interface)
        sub_nodes = sub_nodes.union(set([n for n,_ in self._edges.keys()]))
        for nps in self._edges.values():
            sub_nodes = sub_nodes.union([n for n,_ in nps])

        return sub_nodes

    def visualize(self, dot: graphviz.Digraph):
        all_nodes = self._get_sub_nodes()

        for node in all_nodes:
            node.visualize(dot)

        for from_port, to_ports in self._edges.items():
            from_node, _ = from_port 
            for to_node,_ in to_ports:
                dot.edge(str(from_node.id), str(to_node.id)) # type:ignore 

    def validate(self) -> bool:
        sub_nodes = self._get_sub_nodes()
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

    def __repr__(self) -> str:
        return f"Graph-{self.id}"


class Add(Node):
    def __init__(self, num_inputs: int):
        super().__init__(num_inputs, 1)

    def eval(self, input: List[Any])->List[Any]:
        assert_valid_eval(self.num_inputs, len(input))
        return [sum(input)]
    
    def visualize(self, dot: graphviz.Digraph):
        dot.node(str(self.id), f"+") # type:ignore

    def __repr__(self):
        return f"Add-{super().__repr__()}"
        
class Subtract(Node):
    def __init__(self,):
        super().__init__(2, 1)

    def eval(self, input: List[Any])->List[Any]:
        assert_valid_eval(2, len(input))
        return input[0]-input[1]
    
    def visualize(self, dot: graphviz.Digraph):
        dot.node(str(self.id), f"-") # type:ignore

    def __repr__(self):
        return f"Sub-{super().__repr__()}"

def assert_valid_eval(required_inputs:int, seen_inputs:int):
    if required_inputs!=seen_inputs:
        raise BadEvalArgs()

def assert_in_port_exists(node_port:InPort):
    node, port = node_port
    if port>=node.num_inputs or port<0:
        raise PortDoesntExist(f"Input port {port} for node {node}")


def assert_out_port_exists(node_port:OutPort):
    node, port = node_port
    if port>=node.num_outputs or port<0:
        raise PortDoesntExist(f"Output port {port} for node {node}")

def visualize_graph(g: Graph, out_path:str="Artifacts", out_file_name:str="tmp"):
    dot = graphviz.Digraph()
    g.visualize(dot)

    dot_file_name = os.path.join(out_path, f"{out_file_name}.dot")
    with open(dot_file_name, "w+") as f:
        f.write(dot.source)

    dot.render(dot_file_name) #type:ignore


'''
def Euler2D_X()->Graph:
    g = Graph(4,4)
    p = PlaceHolderNode("p")
    irho = PlaceHolderNode("irho")
    g.add_edge(g.inputs[0], p)
    g.add_edge(g.inputs[1], p)
    g.add_edge(g.inputs[2], p)
    g.add_edge(g.inputs[3], p)

    g.add_edge(g.inputs[0], irho)
    
    g.add_edge(irho, g.outputs[1])
    g.add_edge(irho, g.outputs[2])
    g.add_edge(irho, g.outputs[3])

    g.add_edge(p, g.outputs[2])
    g.add_edge(p, g.outputs[3])

    g.add_edge(g.inputs[1], g.outputs[1])

    g.add_edge(g.inputs[2], g.outputs[0])
    g.add_edge(g.inputs[2], g.outputs[1])
    g.add_edge(g.inputs[2], g.outputs[2])
    g.add_edge(g.inputs[2], g.outputs[3])

    g.add_edge(g.inputs[3], g.outputs[3])
    return g
'''

if __name__=="__main__":
    g=Graph(2,3)
    add = Add(2)
    sub = Subtract()
    g.add_edge(g.get_internal_input(0), g.get_internal_output(0))
    
    g.add_edge(g.get_internal_input(0), (add,0))
    g.add_edge(g.get_internal_input(1), (add,0))
    #g.add_edge(g.get_internal_input(1), (add,1))
    #g.add_edge((add,0), g.get_internal_output(1))
    
    g.add_edge(g.get_internal_input(0), (sub,0))
    g.add_edge(g.get_internal_input(1), (sub,1))
    g.add_edge((sub,0), g.get_internal_output(2))
    e_msg = '\n'.join([e for e in g.validate()])
    print(f"Errors:\n{e_msg}")
    #g = Euler2D_X()
    visualize_graph(g)
