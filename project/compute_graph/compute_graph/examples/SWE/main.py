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
from compute_graph.examples.General.general import rusanov, patchUpdate_2D, source_term_zeros
from compute_graph.examples.SWE.swe_graphs import swe_flux_x, swe_flux_y, swe_max_eigen_x, swe_max_eigen_y, swe_ncp_x, swe_ncp_y

def make_swe():
    make_rus_x:Callable[[str], Graph] = lambda x: rusanov(3,1, 2, swe_max_eigen_x, swe_flux_x, swe_ncp_x, friendly_name=x)
    make_rus_y:Callable[[str], Graph] = lambda x: rusanov(3,1, 2, swe_max_eigen_y, swe_flux_y, swe_ncp_y, friendly_name=x)
    g = patchUpdate_2D(3, 3, 1, make_rus_x, make_rus_y, lambda: source_term_zeros(3, 1, 2))

    in8 = IR_Array(UniqueVariableName("in_patch"), 100)
    in9 = IR_SingleVariable(UniqueVariableName("t"), False)
    in10 = IR_SingleVariable(UniqueVariableName("dt"), False)
    in11 = IR_SingleVariable(UniqueVariableName("patch_center_0"), False)
    in12 = IR_SingleVariable(UniqueVariableName("patch_center_1"), False)
    in13 = IR_SingleVariable(UniqueVariableName("patch_size_0"), False)
    in14 = IR_SingleVariable(UniqueVariableName("patch_size_1"), False)
    
    out8 = IR_Array(UniqueVariableName("out_patch"), 36)
    
    func_stencil:FunctionStencil = {
        'PatchUpdate': ([in9, in10, in11, in12, in13, in14, in8, out8], in8.all_ref()+[in9, in10, in11, in12, in13, in14], out8.all_ref()),
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
            extra_headers=["../../stdlibs.h", "swe_2_base.h"],
            namespace="kernels::swe2"),
        verbose=True,
        output_file="../../Artifacts/swe.g.cpp"
    )
    
    tf_stack.tf(g)


if __name__=="__main__":
    make_swe()