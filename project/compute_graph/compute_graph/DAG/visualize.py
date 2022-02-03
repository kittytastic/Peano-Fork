import graphviz #type: ignore
import os.path
from compute_graph.DAG.dag_visitor import DAG_PropsVisitor 
from compute_graph.DAG.graph import Graph
from compute_graph.local_types import GraphViz

from compute_graph.DAG.ops import Add, Multiply, Subtract
from compute_graph.DAG.primitive_node import InputInterface, OutputInterface, PassThroughNode, TerminalInput

class DAGVizVisitor(DAG_PropsVisitor[None, int]):
    def __init__(self, dot:GraphViz) -> None:
        super().__init__()
        self.dot = dot

    def colour(self, depth: int):
        cols = ["aquamarine3","chocolate2", "steelblue", "gold2", "darkslateblue"]
        return cols[depth]

    def visitGraph(self, node:Graph, props:int)->None:
        all_nodes = node.get_sub_nodes()
        for n in all_nodes:
            if isinstance(n, Graph):
                print("Found a subgraph")
                self.visit(n, props+1)
            else:
                self.visit(n, props)

        for from_port, to_ports in node.get_edges().items():
            from_node, _ = from_port 
            for to_node,_ in to_ports:
                self.dot.edge(str(from_node.id), str(to_node.id)) # type:ignore 

    def visitAdd(self, node:Add, props:int)->None:
        self.dot.node(str(node.id), f"+", color=self.colour(props)) # type:ignore
    
    def visitSubtract(self, node:Subtract, props:int)->None:
        self.dot.node(str(node.id), f"-", color=self.colour(props)) # type:ignore
    
    def visitMultiply(self, node:Multiply, props:int)->None:
        self.dot.node(str(node.id), f"*", color=self.colour(props)) # type:ignore
    
    def visitTerminalInput(self, node:TerminalInput, props:int)->None:
        name = node.friendly_name if node.friendly_name else str(node)
        self.dot.node(str(node.id), f"{name}", color=self.colour(props)) # type:ignore
    
    def visitPassThroughNode(self, node:PassThroughNode, props:int)->None:
        name = node.friendly_name if node.friendly_name else str(node)
        self.dot.node(str(node.id), f"{name}", color=self.colour(props)) # type:ignore
    
    def visitInputInterface(self, node:InputInterface, props:int)->None:
        name = node.friendly_name if node.friendly_name else str(node)
        self.dot.node(str(node.id), f"{name}", color=self.colour(props)) # type:ignore
    
    def visitOutputInterface(self, node:OutputInterface, props:int)->None:
        name = node.friendly_name if node.friendly_name else str(node)
        self.dot.node(str(node.id), f"{name}", color=self.colour(props)) # type:ignore

def visualize_graph(g: Graph, out_path:str="Artifacts", out_file_name:str="tmp"):
    dot = graphviz.Digraph()
    gv = DAGVizVisitor(dot)
    gv.visit(g, 0)

    dot_file_name = os.path.join(out_path, f"{out_file_name}.dot")
    with open(dot_file_name, "w+") as f:
        f.write(dot.source)

    dot.render(dot_file_name, format='png') #type:ignore