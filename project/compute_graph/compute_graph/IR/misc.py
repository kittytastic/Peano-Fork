from typing import Dict, List, Set
from compute_graph.IR.symbols import IR_Array, IR_LooseFunction, IR_MultiAssign, IR_NoReturn, IR_SingleAssign, IR_Symbol, IR_TempVariable, IR_TightFunction, IR_VarArgDefine, IR_VarBodyDefine, IR_Variable, IR_SingleVariable
from compute_graph.IR.transform import IR_Transfrom


class InlineInOut(IR_Transfrom):
    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        working_ir = self.assert_and_cast_symbol_type(in_IR, IR_LooseFunction) 
        working_ir = self.inline_inputs(working_ir)
        print(working_ir)
        working_ir = self.inline_outputs(working_ir)
        

        return working_ir

    def inline_inputs(self, working_ir: IR_LooseFunction)->IR_LooseFunction:
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


    def inline_outputs(self, working_ir: IR_LooseFunction)->IR_LooseFunction:
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


class ApplyCallStencil(IR_Transfrom):
    def __init__(self, target_args: List[IR_Variable], in_map: List[IR_Variable], out_map: List[IR_Variable]):
        self.target_args = target_args
        self.in_map = in_map
        self.out_map = out_map
        super().__init__()

    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        working_ir = self.assert_and_cast_symbol_type(in_IR, IR_LooseFunction) 

        for in_v, target_v in zip(working_ir.in_var, self.in_map):
            working_ir.replace(in_v, target_v) 
        
        for out_v, target_v in zip(working_ir.out_var, self.out_map):
            working_ir.replace(out_v, target_v)

        out_ir = IR_TightFunction(working_ir.data_type, self.target_args, working_ir.body, IR_NoReturn(), working_ir.name)

        return out_ir

class RemoveAllTemp(IR_Transfrom):
    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        working_ir = self.assert_and_cast_symbol_type(in_IR, IR_TightFunction)
        
        temp_vars = working_ir.get_instances(IR_TempVariable)
        new_vars = [IR_SingleVariable(tv.name, False) for tv in temp_vars]
        for nv, tv in zip(new_vars, temp_vars):
            working_ir.replace(tv, nv)
        
        return working_ir

class DefineAllVars(IR_Transfrom):
    def tf(self, in_IR: IR_Symbol)-> IR_Symbol:
        working_ir = self.assert_and_cast_symbol_type(in_IR, IR_TightFunction)
        symbol_table:Set[IR_Variable] = set()

        for idx, a in enumerate(working_ir.args):
            symbol_table.add(a)
            working_ir.args[idx] = IR_VarArgDefine(a)

            if isinstance(a, IR_Array):
                symbol_table.update(a.refs)


        for line in working_ir.body:
            if isinstance(line, IR_MultiAssign):
                raise Exception("Not implemented")
            
            if isinstance(line, IR_SingleAssign):
                assign_var = line.assign_var
                if assign_var not in symbol_table:
                    line.assign_var = IR_VarBodyDefine(assign_var)
                    symbol_table.add(assign_var)

        return working_ir