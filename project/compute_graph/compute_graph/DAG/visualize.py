import graphviz #type: ignore
import os.path
from compute_graph.DAG.dag_visitor import DAG_Visitor 
from compute_graph.DAG.graph import Graph
from compute_graph.local_types import GraphViz

from compute_graph.DAG.ops import Add, Multiply, Subtract
from compute_graph.DAG.primitive_node import InputPassThrough, PassThroughNode, TerminalInput

class DAGVizVisitor(DAG_Visitor[None]):
    def __init__(self, dot:GraphViz) -> None:
        super().__init__()
        self.dot = dot

    def visitGraph(self, node:Graph)->None:
        all_nodes = node.get_sub_nodes()
        for n in all_nodes:
            self.visit(n)

        for from_port, to_ports in node.get_edges().items():
            from_node, _ = from_port 
            for to_node,_ in to_ports:
                self.dot.edge(str(from_node.id), str(to_node.id)) # type:ignore 

    def visitAdd(self, node:Add)->None:
        self.dot.node(str(node.id), f"+") # type:ignore
    
    def visitSubtract(self, node:Subtract)->None:
        self.dot.node(str(node.id), f"-") # type:ignore
    
    def visitMultiply(self, node:Multiply)->None:
        self.dot.node(str(node.id), f"*") # type:ignore
    
    def visitTerminalInput(self, node:TerminalInput)->None:
        name = node.friendly_name if node.friendly_name else str(node)
        self.dot.node(str(node.id), f"{name}") # type:ignore
    
    def visitPassThroughNode(self, node:PassThroughNode)->None:
        name = node.friendly_name if node.friendly_name else str(node)
        self.dot.node(str(node.id), f"{name}") # type:ignore
    
    def visitInputPassThrough(self, node:InputPassThrough)->None:
        return

def visualize_graph(g: Graph, out_path:str="Artifacts", out_file_name:str="tmp"):
    dot = graphviz.Digraph()
    gv = DAGVizVisitor(dot)
    gv.visit(g)

    dot_file_name = os.path.join(out_path, f"{out_file_name}.dot")
    with open(dot_file_name, "w+") as f:
        f.write(dot.source)

    dot.render(dot_file_name) #type:ignore