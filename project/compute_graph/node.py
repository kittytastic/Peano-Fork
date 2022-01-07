from typing import Any, Dict, Optional, Set
import graphviz # type: ignore
from abc import ABC
import os


class MethodNotImplemented(Exception):
    pass

GraphEdges = Dict['Node', Set['Node']]

class Node(ABC):
    next_global_id = 0

    def __init__(self, in_degree: Optional[int], out_degree: Optional[int]):
        self.id = Node.next_global_id
        Node.next_global_id +=1
        self.in_degree = in_degree
        self.out_degree = out_degree

    def visualize_node(self, dot:graphviz.Digraph)->None:
        raise MethodNotImplemented(f"Parent class: {self.__class__.__name__}")

    def __hash__(self) -> int:
        return self.id

    def __str__(self)->str:
        return self.__repr__() 
    
    def __repr__(self) -> str:
        return f"Node_{self.id}"



class GraphInput(Node):
    def __init__(self, g: 'Graph', idx:int):
        super().__init__(None, None)
        self.parent_g = g
        self.idx = idx

    def visualize_node(self, dot: graphviz.Digraph):
        dot.node(str(self.id), f"Gin_{self.idx}") # type:ignore

    def __repr__(self):
        return f"{super().__repr__()}-Gin_{self.idx}"

class GraphOutput(Node):
    def __init__(self, g: 'Graph', idx:int):
        super().__init__(None, None)
        self.parent_g = g
        self.idx = idx
    
    def visualize_node(self, dot: graphviz.Digraph):
        dot.node(str(self.id), f"Gout_{self.idx}") # type:ignore

    def __repr__(self):
        return f"{super().__repr__()}-Gout_{self.idx}"

class Graph():
    def __init__(self, inputs: int, outputs: int):
        self.inputs = [GraphInput(self, i) for i in range(inputs)]
        self.outputs = [GraphOutput(self, i) for i in range(outputs)]
        self._edges: GraphEdges = {}

    def __getitem__(self, key:Node)->Set[Node]:
        return self._edges[key]

    def __setitem__(self, key:Node, value:Set['Node']):
        self._edges[key] = value

    def visualize(self, dot: graphviz.Digraph):
        all_nodes = set(self._edges.keys())
        for n in self._edges.values():
            print(n)
            all_nodes = all_nodes.union(n)

        print(all_nodes)
        for node in all_nodes:
            node.visualize_node(dot)

        for from_node, to_nodes in self._edges.items():
            for to_node in to_nodes:
                dot.edge(str(from_node.id), str(to_node.id)) # type:ignore 

    def add_edge(self, from_node:Node, to_node:Node):
        if from_node in self._edges:
            self._edges[from_node].add(to_node)
        else:
            self._edges[from_node]={to_node}






def visualize_graph(g: Graph, out_path:str="Artifacts", out_file_name:str="tmp"):
    dot = graphviz.Digraph(comment='The Round Table')
    g.visualize(dot)

    dot_file_name = os.path.join(out_path, f"{out_file_name}.dot")
    with open(dot_file_name, "w+") as f:
        f.write(dot.source)

    dot.render(dot_file_name)

if __name__=="__main__":
    g = Graph(2,3)
    g.add_edge(g.inputs[0], g.outputs[0])
    g.add_edge(g.inputs[0], g.outputs[1])
    g.add_edge(g.inputs[1], g.outputs[1])
    g.add_edge(g.inputs[1], g.outputs[2])

    visualize_graph(g)
