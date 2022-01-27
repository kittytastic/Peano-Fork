import graphviz #type: ignore
import os.path
from compute_graph.DAG.dag_visitor import DAGVizVisitor
from compute_graph.DAG.graph import Graph

def visualize_graph(g: Graph, out_path:str="Artifacts", out_file_name:str="tmp"):
    dot = graphviz.Digraph()
    gv = DAGVizVisitor(dot)
    gv.visit(g)

    dot_file_name = os.path.join(out_path, f"{out_file_name}.dot")
    with open(dot_file_name, "w+") as f:
        f.write(dot.source)

    dot.render(dot_file_name) #type:ignore