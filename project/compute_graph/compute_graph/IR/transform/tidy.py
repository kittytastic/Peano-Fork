from typing import Optional, Tuple
from compute_graph.IR.symbols import  IR_LooseFunction,  IR_SingleAssign, IR_Symbol, IR_Variable
from compute_graph.IR.transform.base import IR_Transfrom


class RemoveForwardAlias(IR_Transfrom):
    def __init__(self):
        super().__init__()

    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        working_ir = self.assert_and_cast_symbol_type(in_IR, IR_LooseFunction) 
        
        line_var_cache = [l.get_instances(IR_Variable) for l in working_ir.body]
        next_alias = self._get_next_alias(working_ir, 0)
        while next_alias is not None:
            alias, var, line_idx = next_alias
            working_ir.body = working_ir.body[:line_idx] + working_ir.body[line_idx+1:] 
            line_var_cache = line_var_cache[:line_idx] + line_var_cache[line_idx+1:]

            for i in  range(line_idx, len(working_ir.body)):
                if alias in line_var_cache[i]:
                    working_ir.body[i].replace(alias, var)
                    line_var_cache[i].remove(alias)
                    line_var_cache[i].add(var)

            next_alias = self._get_next_alias(working_ir, line_idx)
        

        return working_ir

    def _get_next_alias(self, func: IR_LooseFunction, start_line: int)->Optional[Tuple[IR_Variable, IR_Variable, int]]:
        for idx in range(start_line, len(func.body)):
            l = func.body[idx]
            if not isinstance(l, IR_SingleAssign): continue
            
            left = l.assign_var
            right = l.expr

            if not isinstance(right, IR_Variable): continue
            if left in func.out_var: continue

            return (left, right, idx)

        return None


class RemoveBackwardsAlias(IR_Transfrom):
    def __init__(self):
        super().__init__()

    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        working_ir = self.assert_and_cast_symbol_type(in_IR, IR_LooseFunction) 

        next_alias = self._get_next_alias(working_ir)
        while next_alias is not None:
            var, alias, line_idx = next_alias
            working_ir.body = working_ir.body[:line_idx] + working_ir.body[line_idx+1:] 
            working_ir.replace(alias, var)

            next_alias = self._get_next_alias(working_ir)
        

        return working_ir

    def _get_next_alias(self, func: IR_LooseFunction)->Optional[Tuple[IR_Variable, IR_Variable, int]]:
        for idx, l in reversed(list(enumerate(func.body))):
            if not isinstance(l, IR_SingleAssign): continue
            
            left = l.assign_var
            right = l.expr

            if not isinstance(right, IR_Variable): continue
            if left not in func.out_var: continue
            if right in func.in_var: continue

            return (left, right, idx)

        return None