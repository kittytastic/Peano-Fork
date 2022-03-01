from typing import Dict, List, Optional, Set, Type, Tuple
from compute_graph.IR.symbols import IR_Array, IR_LooseFunction, IR_MultiAssign, IR_NoReturn, IR_SingleAssign, IR_Symbol, IR_TempVariable, IR_TightFunction, IR_VarArgDefine, IR_VarBodyDefine, IR_Variable, IR_SingleVariable
from compute_graph.IR.symbols.functions import IR_CallLooseFunction, IR_CallTightFunction
from compute_graph.IR.symbols.variables import IR_Assign, IR_DefineOnly
from compute_graph.IR.transform import IR_Transfrom


class InlineInOut(IR_Transfrom):
    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        working_ir = self.assert_and_cast_symbol_type(in_IR, IR_LooseFunction) 
        working_ir = self.inline_inputs(working_ir)
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
            
            if isinstance(line, IR_DefineOnly):
                def_var = line.var
                if def_var not in symbol_table:
                    line.var = IR_VarBodyDefine(def_var)
                
                    if isinstance(def_var, IR_Array):
                        symbol_table.update(def_var.refs)
                        symbol_table.add(def_var)
                    else:
                        symbol_table.add(def_var)
        


        return working_ir


class FilterApply(IR_Transfrom):
    def __init__(self, filter_type: Type[IR_Symbol], apply_tf:IR_Transfrom):
        self.filter_type = filter_type
        self.apply_tf = apply_tf

    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        expr = in_IR.get_instances(self.filter_type)
        list_expr = list(expr)
        tf_expr = [self.apply_tf.tf(ep) for ep in expr]

        for original, new_expr in zip(list_expr, tf_expr):
            in_IR.replace(original, new_expr)
    
        return in_IR

FunctionStencil =  Dict[str, Tuple[List[IR_Variable], List[IR_Variable], List[IR_Variable]]]
class FileApplyCallStencil(IR_Transfrom):
    def __init__(self, func_stencils: FunctionStencil):
         self.func_stencil = func_stencils
    
    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        all_sub_funcs = in_IR.get_instances(IR_LooseFunction)        
        func_map = {sf.name:sf for sf in all_sub_funcs}

        for func_name, og_func in func_map.items():
            if func_name not in self.func_stencil:
                raise Exception(f"Couldn't find a call stencil for the graph {func_name}\nAvaliable stencils: {', '.join(self.func_stencil.keys())}")
            stencil = self.func_stencil[func_name]
            tf = ApplyCallStencil(stencil[0], stencil[1], stencil[2])
            new_func = tf.tf(og_func)
            new_func = self._fix_calls(new_func) # type:ignore

            in_IR.replace(og_func, new_func)

        return in_IR
    
    def _fix_calls(self, function: IR_TightFunction)->IR_TightFunction:
        amendments: List[Tuple[int, List[IR_Assign]]] = []

        for idx, l in enumerate(function.body):
            if isinstance(l, IR_CallLooseFunction):
                stencil = self.func_stencil[l.function_name]
                new_l:List[IR_Assign] = []
                for var in stencil[0]:
                    new_l.append(IR_DefineOnly(var))
                
                for t_iv, c_iv in zip(stencil[1], l.inputs):
                    new_l.append(IR_SingleAssign(t_iv, c_iv))

                new_l.append(IR_CallTightFunction(l.function_name, stencil[0]))

                for t_ov, c_ov in zip(stencil[2], l.outputs):
                    new_l.append(IR_SingleAssign(c_ov, t_ov))

                amendments.append((idx, new_l))
        
        for idx, new_body in reversed(amendments):
            function.body =  function.body[0:idx] + new_body + function.body[idx+1:]

        
        return function


class RemoveForwardAlias(IR_Transfrom):
    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        working_ir = self.assert_and_cast_symbol_type(in_IR, IR_LooseFunction) 

        next_alias = self._get_next_alias(working_ir)
        while next_alias is not None:
            alias, var, line_idx = next_alias
            working_ir.body = working_ir.body[:line_idx] + working_ir.body[line_idx+1:] 
            working_ir.replace(alias, var)

            next_alias = self._get_next_alias(working_ir)
        

        return working_ir

    def _get_next_alias(self, func: IR_LooseFunction)->Optional[Tuple[IR_Variable, IR_Variable, int]]:
        for idx, l in enumerate(func.body):
            if not isinstance(l, IR_SingleAssign): continue
            
            left = l.assign_var
            right = l.expr

            if not isinstance(right, IR_Variable): continue
            if left in func.out_var: continue

            return (left, right, idx)

        return None


class RemoveBackwardsAlias(IR_Transfrom):
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

class IR_TF_STOP(IR_Transfrom):
    def tf(self, in_IR: IR_Symbol) -> IR_Symbol:
        exit()