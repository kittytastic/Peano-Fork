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
from compute_graph.examples.General.general import *
from compute_graph.examples.Euler.proper_euler import *
from compute_graph.examples.Euler.neat_euler import *



def make_neat_euler():
    make_rus_x:Callable[[str], Graph] = lambda x: rusanov_neat(max_eigen_x, flux_x, friendly_name=x)
    make_rus_y:Callable[[str], Graph] = lambda x: rusanov_neat(max_eigen_y, flux_y, friendly_name=x)
    g = patchUpdate_neat(3, 2, 4, make_rus_x, make_rus_y)


    in1 = IR_Array(UniqueVariableName("input"), 4)
    out1 = IR_Array(UniqueVariableName("out"), 4)
    
    in3 = IR_Array(UniqueVariableName("in_p"), 4)
    out3 = IR_Array(UniqueVariableName("out_p"), 1)
    
    in4 = IR_Array(UniqueVariableName("in_irho"), 1)
    out4 = IR_Array(UniqueVariableName("out_irho"), 1)

    in5 = IR_Array(UniqueVariableName("in_max_eig_x"), 4)
    out5 = IR_Array(UniqueVariableName("out_max_eig_x"), 1)
    
    in6 = IR_Array(UniqueVariableName("in_max_eig_y"), 4)
    out6 = IR_Array(UniqueVariableName("out_max_eig_y"), 1)
    
    in7 = IR_Array(UniqueVariableName("in_rusanov"), 8)
    out7 = IR_Array(UniqueVariableName("out_rusanov"), 4)
    
    in8 = IR_Array(UniqueVariableName("in_patch"), 100)
    in9 = IR_SingleVariable(UniqueVariableName("t"), False)
    in10 = IR_SingleVariable(UniqueVariableName("dt"), False)
    in11 = IR_SingleVariable(UniqueVariableName("patch_center_0"), False)
    in12 = IR_SingleVariable(UniqueVariableName("patch_center_1"), False)
    in13 = IR_SingleVariable(UniqueVariableName("patch_size_0"), False)
    in14 = IR_SingleVariable(UniqueVariableName("patch_size_1"), False)
    
    out8 = IR_Array(UniqueVariableName("out_patch"), 36)
    
    func_stencil:FunctionStencil = {
        'flux_x': ([in1, out1], in1.all_ref(), out1.all_ref()),
        'max_eigen_x': ([in5, out5], in5.all_ref(), out5.all_ref()),
        'max_eigen_y': ([in6, out6], in6.all_ref(), out6.all_ref()),
        'rusanov': ([in7, out7], in7.all_ref(), out7.all_ref()),
        'PatchUpdate': ([in9, in10, in11, in12, in13, in14, in8, out8], in8.all_ref()+[in9, in10, in11, in12, in13, in14], out8.all_ref()),
        'p': ([in3, out3], in3.all_ref(), out3.all_ref()),
        'irho': ([in4, out4], in4.all_ref(), out4.all_ref())
    }

    
    tf_stack = FullStackTransform(
        DAG_TransformChain([
            #DAG_Viz(file_name = "before", max_depth=1),
            DAG_Flatten(),
            #DAG_Viz(file_name = "after", max_depth=None),
        ]),
        IR_TransformChain([
            #IR_TF_STOP(),
            FilterApply(IR_LooseFunction, RemoveForwardAlias()),
            FilterApply(IR_LooseFunction, RemoveBackwardsAlias()),
            FileApplyCallStencil(func_stencil),
            FilterApply(IR_TightFunction, RemoveAllTemp()),
            FilterApply(IR_TightFunction, DefineAllVars()),
        ],
        large_output_mode="../../Artifacts"),
        C_Backend(
            extra_headers=["../../stdlibs.h", "kernel_3_base.h"],
            namespace="kernels::k3"),
        verbose=True
    )
    
    code = tf_stack.tf(g)

    with open("../../Artifacts/out-code.cpp", "w+") as f:
        f.write(code)



def make_proper_euler():
    make_rus_x:Callable[[str], Graph] = lambda x: rusanov(4, proper_max_eigen_x, proper_flux_x, friendly_name=x)
    make_rus_y:Callable[[str], Graph] = lambda x: rusanov(4, proper_max_eigen_y, proper_flux_y, friendly_name=x)
    g = patchUpdate_2D(3, 4, make_rus_x, make_rus_y, source_term)

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
            DAG_Viz(file_name = "after", max_depth=1),
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
            extra_headers=["../../stdlibs.h", "kernel_3_base.h"],
            namespace="kernels::k3"),
        verbose=True,
        output_file="../../Artifacts/out-code.cpp"
    )
    
    tf_stack.tf(g)


if __name__=="__main__":
    #make_neat_euler()
    make_proper_euler()
