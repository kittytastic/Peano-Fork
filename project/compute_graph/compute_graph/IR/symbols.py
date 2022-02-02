from typing import List, TypeVar, Union, Tuple, Any, Optional, cast, Type, Set
from enum import Enum
import inspect

_T = TypeVar("_T")

class IR_DataTypes(Enum):
    VOID = 0
    FP64 = 1

class IR_Symbol():
    def _get_all_attributes(self)->List[Tuple[str, Any]]:
        attributes = inspect.getmembers(self, lambda a:not(inspect.isroutine(a)))
        attributes = [a for a in attributes if not(a[0].startswith('__') and a[0].endswith('__'))]
        return attributes

    def _is_list_of_symbol(self, in_list:Any)->Optional[List['IR_Symbol']]:
        if not isinstance(in_list, list):
            return None
        
        in_list = cast(List[Any], in_list)
        for i in in_list:
            if not isinstance(i, IR_Symbol):
                return None
        
        return in_list
    

    def __contains__(self, key:Union['IR_Symbol', type]):
        if inspect.isclass(key):
            if isinstance(self, key):
                return True
        else:
            if key == self:
                return True
        
        attributes = self._get_all_attributes()
        child_ins:List[bool] = [key in val for _, val in attributes if isinstance(val, IR_Symbol)]
        
        child_sym_lists:List[List['IR_Symbol']] = [l for _,l in attributes if self._is_list_of_symbol(l)]
        child_list_ins: List[bool] = [key in i for l in child_sym_lists for i in l]

        return any(child_ins) or any(child_list_ins)
    
    def replace(self, find:'IR_Symbol', replace: 'IR_Symbol')->int:
        if find == self:
            raise Exception("Cannot replace. The symbol you called replace on needs to be replaced")

        attributes = self._get_all_attributes() 
        child_symbols = [(k,v) for k, v in attributes if isinstance(v, IR_Symbol)]
        child_lists:List[Tuple[str,List['IR_Symbol']]] = [(k,l) for k,l in attributes if self._is_list_of_symbol(l)]

        replacement_count = 0
        for k, s in child_symbols:
            if s == find:
                setattr(self, k, replace)
                replacement_count +=1
            else:
                replacement_count += s.replace(find, replace)

        for k, l in child_lists:
            l_ref = getattr(self, k)
            for idx, v in enumerate(l):
                if v==find:
                    l_ref[idx] = replace
                    replacement_count +=1
                else:
                    replacement_count += v.replace(find, replace)


        return replacement_count
    
    def get_instances(self, symbol_type: Type[_T])->Set[_T]:
        if isinstance(self, symbol_type):
            return set([self])
        
        attributes = self._get_all_attributes() 
        child_symbols = [s for _, s in attributes if isinstance(s, IR_Symbol)]
        child_lists:List[List['IR_Symbol']] = [l for _,l in attributes if self._is_list_of_symbol(l)]

        instances_from_syms = [s.get_instances(symbol_type) for s in child_symbols]
        instances_from_list = [s.get_instances(symbol_type) for l in child_lists for s in l]

        base_set: Set[_T] =  set()
        base_set = base_set.union(*instances_from_syms)
        base_set = base_set.union(*instances_from_list)
        return base_set

class IR_LooseFunction(IR_Symbol):
    def __init__(self, data_type:IR_DataTypes, in_var: List['IR_Variable'], out_var: List['IR_Variable'], body: List['IR_Assign']):
        self.data_type = data_type
        self.in_var = in_var
        self.out_var = out_var
        self.body = body
    
    def __str__(self):
        in_var_str = ", ".join([str(iv) for iv in self.in_var])
        out_var_str = ", ".join([str(iv) for iv in self.out_var])
        body_str = "\n\t".join([str(b) for b in self.body])
        out_str = f"define {self.data_type} ({in_var_str}) ({out_var_str}):\n\t{body_str}"
        return out_str

class IR_TightFunction(IR_Symbol):
    def __init__(self, data_type:IR_DataTypes, args: List['IR_Variable'], body: List['IR_Assign'], return_statement: 'IR_Return'):
        self.data_type = data_type
        self.args = args
        self.body = body
        self.return_statement = return_statement
    
    def __str__(self):
        arg_str = ", ".join([str(a) for a in self.args])
        body_str = "\n\t".join([str(b) for b in self.body])
        out_str = f"define {self.data_type} ({arg_str}):\n\t{body_str}\n\t{str(self.return_statement)}"
        return out_str   

class IR_Return(IR_Symbol): pass
class IR_ReturnValue(IR_Return):
    def __str__(self) -> str:
        return "<return something>"

class IR_NoReturn(IR_Return):
    def __str__(self) -> str:
        return "<return nothing>"

class IR_Assign(IR_Symbol):
    pass

class IR_SingleAssign(IR_Assign):
    def __init__(self, assign_var: 'IR_Variable', expr: 'IR_Symbol'):
        self.assign_var = assign_var
        self.expr = expr

    def __str__(self) -> str:
        return f"{self.assign_var} = {self.expr}"

class IR_MultiAssign(IR_Assign):
    def __init__(self, assign_vars: List['IR_Variable'], func: 'IR_CallLooseFunction'):
        self.assign_vars = assign_vars
        self.func = func

class IR_Add(IR_Symbol):
    def __init__(self, lval: IR_Symbol, rval: IR_Symbol):
        self.lval = lval
        self.rval = rval
    
    def __str__(self):
        return f"{self.lval} + {self.rval}"

class IR_Sub(IR_Symbol):
    def __init__(self, lval: IR_Symbol, rval: IR_Symbol):
        self.lval = lval
        self.rval = rval

    def __str__(self):
        return f"{self.lval} - {self.rval}"

class IR_Mul(IR_Symbol):
    def __init__(self, lval: IR_Symbol, rval: IR_Symbol):
        self.lval = lval
        self.rval = rval
    
    def __str__(self):
        return f"{self.lval} * {self.rval}"

class IR_Variable(IR_Symbol):
    def __init__(self):
        super().__init__()
    
    def __repr__(self) -> str:
        return self.__str__()


class IR_TempVariable(IR_Variable):
    def __init__(self, tmp_class:str, id:int) -> None:
        self.tmp_class = tmp_class
        self.id = id

    def __str__(self):
        return f"%{self.tmp_class}{self.id}"

    def __repr__(self) -> str:
        return self.__str__()

class IR_SingleVariable(IR_Variable):
    def __init__(self, name:str, is_ref:bool) -> None:
        self.name = name
        self.is_ref = is_ref

    def __str__(self):
        return f"#{self.name}"

class IR_Array(IR_Variable):
    def __init__(self, name:str, length:int) -> None:
        self.length = length
        self.name = name
        self.refs = [IR_ArrayRef(self.name, i) for i in range(length)]

    def get_ref(self, idx: int):
        return self.refs[idx]

    def __str__(self):
        return f"#list({self.name})"

class IR_VarBodyDefine(IR_Variable):
    def __init__(self, var: IR_Variable):
        self.var = var

    def __str__(self):
        return f"new {str(self.var)}"

class IR_VarArgDefine(IR_Variable):
    def __init__(self, var: IR_Variable):
        self.var = var
    
    def __str__(self):
        return f"new {str(self.var)}"
        


class IR_ArrayRef(IR_Variable):
    def __init__(self, parent_name:str, id:int) -> None:
        self.parent_name = parent_name
        self.id = id

    def __str__(self):
        return f"#{self.parent_name}[{self.id}]"


class IR_CallLooseFunction(IR_Symbol):
    def __init__(self, args: List['IR_Variable']):
        self.args = args