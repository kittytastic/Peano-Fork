from typing import Dict, Set, List
from compute_graph.IR.symbols import IR_Function, IR_SingleAssign, IR_Symbol, IR_TempVariable, IR_Variable
from compute_graph.IR.transform import IR_Transfrom


class InlineInOut(IR_Transfrom):
    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        working_ir = self.assert_and_cast_symbol_type(in_IR, IR_Function) 
        working_ir = self.inline_inputs(working_ir)
        print(working_ir)
        working_ir = self.inline_outputs(working_ir)
        

        return working_ir

    def inline_inputs(self, working_ir: IR_Function)->IR_Function:
        in_vars = working_ir.in_var
        invar_alias: Dict[IR_Variable, IR_Variable] = {}
        delete_lines:List[int] = []

        for idx, l in enumerate(working_ir.body):
            if isinstance(l, IR_SingleAssign):
                if l.expr in in_vars:
                    invar_alias[l.expr] = l.assign_var
                    delete_lines.append(idx)

        for idx in reversed(delete_lines):
            del working_ir.body[idx]

        for iv, alias in invar_alias.items():
            for l in working_ir.body:
                l.replace(alias, iv)
            
        
        return working_ir


    def inline_outputs(self, working_ir: IR_Function)->IR_Function:
        out_vars = working_ir.out_var
        outvar_alias: Dict[IR_Variable, IR_Variable] = {}
        delete_lines:List[int] = []

        for idx, l in enumerate(working_ir.body):
            if isinstance(l, IR_SingleAssign):
                if l.assign_var in out_vars:
                    assert(isinstance(l.expr, IR_Variable))
                    outvar_alias[l.assign_var] = l.expr
                    delete_lines.append(idx)

        for idx in reversed(delete_lines):
            del working_ir.body[idx]

        for iv, alias in outvar_alias.items():
            for l in working_ir.body:
               l.replace(alias, iv)
            
        
        return working_ir
    