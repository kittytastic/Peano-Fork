from typing import Optional
import graphviz #type: ignore
import os.path
from compute_graph.DAG.dag_visitor import DAG_PropsVisitor 
from compute_graph.DAG.graph import Graph, InputInterface, OutputInterface
from compute_graph.local_types import GraphViz

from compute_graph.DAG.ops import Add, Divide, Multiply, Subtract
from compute_graph.DAG.primitive_node import Constant, PassThroughNode, TerminalInput

class DAGVizVisitor(DAG_PropsVisitor[None, int]):
    def __init__(self, dot:GraphViz, max_depth:Optional[int]=None) -> None:
        super().__init__()
        self.dot = dot
        self.max_depth = max_depth if max_depth is not None else -1

    def colour(self, depth: int):
        cols = ["aquamarine3","chocolate2", "steelblue", "gold2", "darkslateblue"]
        return cols[depth]

    def _exceed_max_depth(self, depth:int)->bool:
        return self.max_depth>=0 and depth>=self.max_depth

    def visitGraph(self, node:Graph, props:int)->None:
        if self._exceed_max_depth(props):
            self.dot.node(str(node.id), str(node.friendly_name), color=self.colour(props)) # type: ignore
            return

        sub_nodes, sub_graphs = node.get_categoriesed_sub_nodes()
        for n in sub_nodes:
            self.visit(n, props)
            
        for g in sub_graphs:
            self.visit(g, props+1)
            
        for from_port, to_ports in node.get_edges().items():
            from_node, _ = from_port
            if isinstance(from_node, Graph) and not self._exceed_max_depth(props+1):
                from_node = from_node.output_interface[from_port[1]]
            
            for to_node, idx  in to_ports:
                if isinstance(to_node, Graph) and not self._exceed_max_depth(props+1):
                    to_node = to_node.input_interface[idx]
                self.dot.edge(str(from_node.id), str(to_node.id)) # type:ignore 

    def visitAdd(self, node:Add, props:int)->None:
        self.dot.node(str(node.id), f"+", color=self.colour(props)) # type:ignore
    
    def visitSubtract(self, node:Subtract, props:int)->None:
        self.dot.node(str(node.id), f"-", color=self.colour(props)) # type:ignore
    
    def visitMultiply(self, node:Multiply, props:int)->None:
        self.dot.node(str(node.id), f"*", color=self.colour(props)) # type:ignore
    
    def visitDivide(self, node:Divide, props:int)->None:
        self.dot.node(str(node.id), f"/", color=self.colour(props)) # type:ignore
    
    def visitConstant(self, node:Constant, props:int)->None:
        self.dot.node(str(node.id), f"{node.value}", color=self.colour(props)) # type:ignore
    
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

def visualize_graph(g: Graph, out_path:str="Artifacts", out_file_name:str="tmp", max_depth:Optional[int]=None):
    dot = graphviz.Digraph()
    gv = DAGVizVisitor(dot, max_depth=max_depth)
    gv.visit(g, 0)

    dot_file_name = os.path.join(out_path, f"{out_file_name}.dot")
    with open(dot_file_name, "w+") as f:
        f.write(dot.source)

    dot.render(dot_file_name, format='png') #type:ignore