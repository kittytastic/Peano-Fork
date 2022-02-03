from typing import Optional, List, Dict
import graphviz #type: ignore
import os.path
from compute_graph.DAG.dag_visitor import DAG_PropsVisitor 
from compute_graph.DAG.graph import Graph
from compute_graph.DAG.node import DAG_Node
from compute_graph.local_types import GraphViz

from compute_graph.DAG.ops import Add, Multiply, Subtract
from compute_graph.DAG.primitive_node import InputInterface, OutputInterface, PassThroughNode, TerminalInput

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
            self.dot.node(str(node.id), str(node.friendly_name)) # type: ignore
            return

        all_nodes = node.get_sub_nodes()
        sub_graphs:List[Graph] = [] 
        sub_nodes:List[DAG_Node] = [] 
        for n in all_nodes:
            if isinstance(n, Graph):
                sub_graphs.append(n)
                self.visit(n, props+1)
            else:
                sub_nodes.append(n)
                self.visit(n, props)

        node_map: Dict[DAG_Node, DAG_Node] = {sn: sn for sn in sub_nodes}
        for sg in sub_graphs:
            if not self._exceed_max_depth(props+1):
                input_maps = {in_if: in_if for in_if in sg.input_interface}
                output_maps = {out_if: out_if for out_if in sg.output_interface}
                node_map = {**node_map, **input_maps, **output_maps}
            else:
                input_maps = {in_if: sg for in_if in sg.input_interface}
                output_maps = {out_if: sg for out_if in sg.output_interface}
                node_map = {**node_map, **input_maps, **output_maps}

        for from_port, to_ports in node.get_edges().items():
            from_node, _ = from_port 
            for to_node,_ in to_ports:
                mapped_from_node = node_map[from_node]
                mapped_to_node = node_map[to_node]
                self.dot.edge(str(mapped_from_node.id), str(mapped_to_node.id)) # type:ignore 

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
    gv = DAGVizVisitor(dot, max_depth=-1)
    gv.visit(g, 0)

    dot_file_name = os.path.join(out_path, f"{out_file_name}.dot")
    with open(dot_file_name, "w+") as f:
        f.write(dot.source)

    dot.render(dot_file_name, format='png') #type:ignore