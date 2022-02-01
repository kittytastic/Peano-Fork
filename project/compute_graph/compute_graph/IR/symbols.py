from typing import List, Union, Tuple, Any, Optional
from enum import Enum
import inspect


class IR_DataTypes(Enum):
    FP64 = 1

class IR_Symbol():
    def _get_all_attributes(self)->List[Tuple[str, Any]]:
        attributes = inspect.getmembers(self, lambda a:not(inspect.isroutine(a)))
        attributes = [a for a in attributes if not(a[0].startswith('__') and a[0].endswith('__'))]
        return attributes

    def _is_list_of_symbol(self, in_list:List[Any])->Optional[List['IR_Symbol']]:
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
        
        child_lists: List[List[Any]] = [val for _,val in attributes if isinstance(val, list)]
        child_sym_lists:List[List['IR_Symbol']] = [l for l in child_lists if self._is_list_of_symbol(l)]
        child_list_ins: List[bool] = [key in i for l in child_sym_lists for i in l]

        return any(child_ins) or any(child_list_ins)
    
    def replace(self, find:'IR_Symbol', replace: 'IR_Symbol')->int:
        # TODO wont work with literal attributes
        if find == self:
            raise Exception("Cannot replace. The symbol yoy called replace on needs to be replaced")

        attributes = inspect.getmembers(self, lambda a:not(inspect.isroutine(a)))
        attributes = [a for a in attributes if not(a[0].startswith('__') and a[0].endswith('__'))]
        child_symbol = [(k,v) for k, v in attributes if isinstance(v, IR_Symbol)]

        replacement_count = 0
        for k, s in child_symbol:
            if s == find:
                setattr(self, k, replace)
                replacement_count +=1
            else:
                replacement_count += s.replace(find, replace)

        return replacement_count

class IR_Function(IR_Symbol):
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

    

class IR_Assign(IR_Symbol):
    pass

class IR_SingleAssign(IR_Assign):
    def __init__(self, assign_var: 'IR_Variable', expr: 'IR_Symbol'):
        self.assign_var = assign_var
        self.expr = expr

    def __str__(self) -> str:
        return f"{self.assign_var} = {self.expr}"

class IR_MultiAssign(IR_Assign):
    def __init__(self, assign_vars: List['IR_Variable'], func: 'IR_CallFunction'):
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

class IR_TempVariable(IR_Variable):
    def __init__(self, tmp_class:str, id:int) -> None:
        self.tmp_class = tmp_class
        self.id = id

    def __str__(self):
        return f"%{self.tmp_class}{self.id}"

    def __repr__(self) -> str:
        return self.__str__()

class IR_CallFunction(IR_Symbol):
    def __init__(self, args: List['IR_Variable']):
        self.args = args