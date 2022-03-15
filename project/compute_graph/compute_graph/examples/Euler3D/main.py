from typing import Callable
from compute_graph.DAG import *
from compute_graph.DAG.transform import DAG_Flatten, DAG_TransformChain, DAG_Viz, DAG_RemovePassThrough, DAG_RemoveUnusedComp
from compute_graph.DAG.transform.simplify import DAG_RemoveArithmeticNoOps, DAG_RemoveDuplicatedArithmetic
from compute_graph.IR.symbols.variables import IR_SingleVariable
from compute_graph.IR.transform import IR_TransformChain, DefineAllVars, FileApplyCallStencil, FilterApply, FunctionStencil,  RemoveAllTemp, RemoveBackwardsAlias, RemoveForwardAlias
from compute_graph.IR.symbols import IR_Array,  UniqueVariableName
from compute_graph.IR.symbols.functions import  IR_LooseFunction, IR_TightFunction
from compute_graph.language_backend.c import C_Backend
from compute_graph.transform import FullStackTransform
from compute_graph.examples.General.general import rusanov, patchUpdate_3D, source_term_zeros
from compute_graph.examples.Euler3D.euler3d_graphs import *

def make_euler3d():
    make_rus_x:Callable[[str], Graph] = lambda x: rusanov(5,0, 3, max_eigen_x, flux_x, None, friendly_name=x)
    make_rus_y:Callable[[str], Graph] = lambda x: rusanov(5,0, 3, max_eigen_y, flux_y, None, friendly_name=x)
    make_rus_z:Callable[[str], Graph] = lambda x: rusanov(5,0, 3, max_eigen_z, flux_z, None, friendly_name=x)
    g = patchUpdate_3D(3, 5, 0, make_rus_x, make_rus_y, make_rus_z, lambda: source_term_zeros(5, 0, 3))

    in8 = IR_Array(UniqueVariableName("in_patch"), 625)
    in9 = IR_SingleVariable(UniqueVariableName("t"), False)
    in10 = IR_SingleVariable(UniqueVariableName("dt"), False)
    in11 = IR_SingleVariable(UniqueVariableName("patch_center_0"), False)
    in12 = IR_SingleVariable(UniqueVariableName("patch_center_1"), False)
    in125 = IR_SingleVariable(UniqueVariableName("patch_center_2"), False)
    in13 = IR_SingleVariable(UniqueVariableName("patch_size_0"), False)
    in14 = IR_SingleVariable(UniqueVariableName("patch_size_1"), False)
    in15 = IR_SingleVariable(UniqueVariableName("patch_size_2"), False)
    
    out8 = IR_Array(UniqueVariableName("out_patch"), 135)
    
    func_stencil:FunctionStencil = {
        'PatchUpdate': ([in9, in10, in11, in12, in125, in13, in14, in15, in8, out8], in8.all_ref()+[in9, in10, in11, in12, in125, in13, in14, in15], out8.all_ref()),
    }

    
    tf_stack = FullStackTransform(
        DAG_TransformChain([
            #DAG_Viz(file_name = "before", max_depth=1),
            #DAG_Viz(file_name = "before_flat", max_depth=None),
            DAG_Flatten(),
            DAG_RemovePassThrough(),
            DAG_RemoveUnusedComp(),
            DAG_RemoveArithmeticNoOps(),
            DAG_RemovePassThrough(),
            DAG_RemoveDuplicatedArithmetic(),
            #DAG_Viz(file_name = "after", max_depth=1),
        ]),
        IR_TransformChain([
            FilterApply(IR_LooseFunction, RemoveForwardAlias()),
            FilterApply(IR_LooseFunction, RemoveBackwardsAlias()),
            FileApplyCallStencil(func_stencil),
            FilterApply(IR_TightFunction, RemoveAllTemp()),
            FilterApply(IR_TightFunction, DefineAllVars()),
        ],
        large_output_mode="../../Artifacts"),
        C_Backend(
            extra_headers=["../../stdlibs.h", "euler3d_2_base.h"],
            namespace="kernels::euler3d2"),
        verbose=True,
        output_file="../../Artifacts/euler3d.g.cpp"
    )
    
    tf_stack.tf(g)


if __name__=="__main__":
    make_euler3d()