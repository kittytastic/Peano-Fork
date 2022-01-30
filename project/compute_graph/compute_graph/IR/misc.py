from typing import Dict, Set, List
from compute_graph.IR.symbols import IR_Function, IR_SingleAssign, IR_Symbol, IR_TempVariable, IR_Variable
from compute_graph.IR.transform import IR_Transfrom


class InlineInOut(IR_Transfrom):
    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        working_ir = self.assert_and_cast_symbol_type(in_IR, IR_Function) 

        in_vars = working_ir.in_var
        invar_alias: Dict[IR_Variable, IR_Variable] = {}
        delete_lines:List[int] = []

        for idx, l in enumerate(working_ir.body):
            if isinstance(l, IR_SingleAssign):
                if l.expr in in_vars:
                    invar_alias[l.expr] = l.assign_var
                    delete_lines.append(idx)

        print(invar_alias)
        for idx in reversed(delete_lines):
            del working_ir.body[idx]
        
        #print("delete assigns")
        #print(str(in_IR))

        for iv, alias in invar_alias.items():
            to_fix: List[bool] = []
            for l in working_ir.body:
                is_in = alias in l
                to_fix.append(is_in) 
            print(f"{alias}->{iv}: {to_fix}")

            replace_c:List[int] = [] 
            for l in working_ir.body:
                replace_c.append(l.replace(alias, iv))
            
            print(f"       :{replace_c}")

        return working_ir
        


    