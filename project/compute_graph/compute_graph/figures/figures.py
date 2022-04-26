from typing import List, Optional, Tuple
from compute_graph.DAG import Graph
from compute_graph.DAG.ops import Add, Multiply, Subtract
from compute_graph.DAG.transform.base import DAG_TransformChain
from compute_graph.DAG.transform.flatten import DAG_Flatten
from compute_graph.DAG.transform.tidy import DAG_RemovePassThrough
from compute_graph.DAG.visualize import visualize_graph
import os
from PIL import Image
from compute_graph.IR.symbols.functions import IR_LooseFunction, IR_TightFunction
from compute_graph.IR.symbols.variables import IR_Array, UniqueVariableName
from compute_graph.IR.transform.base import FilterApply, IR_TransformChain
from compute_graph.IR.transform.build import DefineAllVars, FileApplyCallStencil, FunctionStencil, RemoveAllTemp
from compute_graph.IR.transform.tidy import RemoveBackwardsAlias, RemoveForwardAlias
from compute_graph.DAG.IR_tf import dag_to_IR
import numpy as np


def generate_figure(g: Graph, name: str, max_depth:Optional[int]=None):
    visualize_graph(g, out_path="../Artifacts", out_file_name=name, max_depth=max_depth)
    print(f"Generated figure: {name}")


def pil_grid(image_names:List[str], max_horiz:int=np.iinfo(int).max):
    images = [ Image.open(i) for i in image_names ]
    n_images = len(images)
    n_horiz = min(n_images, max_horiz)
    h_sizes, v_sizes = [0] * n_horiz, [0] * (n_images // n_horiz)
    for i, im in enumerate(images):
        h, v = i % n_horiz, i // n_horiz
        h_sizes[h] = max(h_sizes[h], im.size[0])
        v_sizes[v] = max(v_sizes[v], im.size[1])
    h_sizes, v_sizes = np.cumsum([0] + h_sizes), np.cumsum([0] + v_sizes)
    im_grid = Image.new('RGB', (h_sizes[-1], v_sizes[-1]), color='white')
    for i, im in enumerate(images):
        im_grid.paste(im, (h_sizes[i % n_horiz], v_sizes[i // n_horiz]))
    return im_grid



def generate_multi_fig(graphs: List[Tuple[Graph, Optional[int]]], name:str):
    
    for idx, (g, d) in enumerate(graphs):
        generate_figure(g, f"{name}-part{idx}", max_depth=d)

    img = pil_grid([os.path.join("../Artifacts", f"{name}-part{idx}.png") for idx in range(len(graphs))])

    img.save(os.path.join("../Artifacts", f"{name}.png"))

    



def basic_g_6()->Graph:
        g_bottom = Graph(2, 1, "bottom")
        
        add1 = Add(2)
        add2 = Add(2)
        add3 = Add(2)
        add4 = Add(2)
        add5 = Add(2)
        
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), g_bottom.get_internal_input(1)], add1)
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0), g_bottom.get_internal_input(1)], add2)
        g_bottom.fill_node_inputs([add1, add2], add3)
        g_bottom.fill_node_inputs([add1, add2], add4)
        g_bottom.fill_node_inputs([add3, add4], add5)
        g_bottom.add_edge((add5, 0), g_bottom.get_internal_output(0))

        return  g_bottom

def basic_nested_example()->Graph:
        g_top = Graph(2, 1, "top")
        g_bottom = Graph(1, 1, "cubed")
        add1 = Add(2)
        mul1 = Multiply(3)
        
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0),  g_bottom.get_internal_input(0), g_bottom.get_internal_input(0)], mul1)
        g_bottom.add_edge((mul1, 0), g_bottom.get_internal_output(0))
        
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(0))
        g_top.fill_node_inputs([g_bottom.get_external_output(0), g_top.get_internal_input(1)], add1)
        g_top.add_edge((add1, 0), g_top.get_internal_output(0))

        return g_top

def basic_nested_array_output()->Graph:
        g_top = Graph(2, 2, "kernel")
        g_bottom = Graph(1, 1, "cubed")
        add1 = Add(2)
        sub1 = Subtract()
        mul1 = Multiply(3)
        
        g_bottom.fill_node_inputs([g_bottom.get_internal_input(0),  g_bottom.get_internal_input(0), g_bottom.get_internal_input(0)], mul1)
        g_bottom.add_edge((mul1, 0), g_bottom.get_internal_output(0))
        
        g_top.add_edge(g_top.get_internal_input(0), g_bottom.get_external_input(0))
        g_top.fill_node_inputs([g_bottom.get_external_output(0), g_top.get_internal_input(1)], add1)
        g_top.add_edge((add1, 0), g_top.get_internal_output(0))
        g_top.fill_node_inputs([g_bottom.get_external_output(0), g_top.get_internal_input(1)], sub1)
        g_top.add_edge((sub1, 0), g_top.get_internal_output(1))

        return g_top


def example_tight_vs_loose_IR():
    dag_tfs = DAG_TransformChain([
        DAG_Flatten(),
        DAG_RemovePassThrough(),
        ])

    in1 = IR_Array(UniqueVariableName("in"), 2)
    out1 = IR_Array(UniqueVariableName("out"), 2)
    
    func_stencil:FunctionStencil = {
        'kernel': ([in1, out1], in1.all_ref(), out1.all_ref()),
    }

    ir_tfs = IR_TransformChain([
        FilterApply(IR_LooseFunction, RemoveForwardAlias()),
        FilterApply(IR_LooseFunction, RemoveBackwardsAlias()),
        FileApplyCallStencil(func_stencil),
        FilterApply(IR_TightFunction, RemoveAllTemp()),
        FilterApply(IR_TightFunction, DefineAllVars()),
    ])

    g = basic_nested_array_output()
    g = dag_tfs.tf(g)
    generate_figure(g, "tight_vs_loose")
    start_ir = dag_to_IR(g)
    with open("../Artifacts/tight_vs_loose-start.txt", "w+") as f: f.write(str(start_ir))
    
    end_ir = ir_tfs.tf(start_ir)
    with open("../Artifacts/tight_vs_loose-end.txt", "w+") as f: f.write(str(end_ir))

def example_flatten():
    g_before = basic_nested_array_output()
    g_after = basic_nested_array_output()
    tf = DAG_Flatten()
    g_after = tf.tf(g_after)

    generate_multi_fig([
        (g_before, None),
        (g_before, 1),
        (g_after, None),
        ], "flatten")


   
if __name__=="__main__":
    print("--------- Figures -------")
    generate_figure(basic_g_6(), "basic6")
    generate_figure(basic_nested_example(), "basic3")
    
    generate_multi_fig([
        (basic_nested_example(), None),
        (basic_nested_example(), 1),
        ], "basic-nested")
    
    example_tight_vs_loose_IR()
    example_flatten()