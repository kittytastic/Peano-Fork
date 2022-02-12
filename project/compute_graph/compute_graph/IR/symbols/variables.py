from typing import List, NewType
from abc import ABC

from compute_graph.IR.symbols.symbol_base import IR_Symbol

UniqueVariableName = NewType("UniqueVariableName", str)

class IR_Variable(IR_Symbol, ABC):
    def __init__(self, name:UniqueVariableName):
        super().__init__()
        self.name = name
    
    def __repr__(self) -> str:
        return self.__str__()


class IR_TempVariable(IR_Variable):
    def __init__(self, name:UniqueVariableName) -> None:
        super().__init__(name)
    
    def __str__(self):
        return f"%{self.name}"


class IR_SingleVariable(IR_Variable):
    def __init__(self, name:UniqueVariableName, is_ref:bool) -> None:
        super().__init__(name)
        self.is_ref = is_ref

    def __str__(self):
        return f"#{self.name}"

class IR_Array(IR_Variable):
    def __init__(self, name:UniqueVariableName, length:int) -> None:
        super().__init__(name)
        self.length = length
        self.refs = [IR_ArrayRef(self.name, i) for i in range(length)]

    def get_ref(self, idx: int):
        return self.refs[idx]
    
    def all_ref(self)->List[IR_Variable]:
        return self.refs # type: ignore

    def __str__(self):
        return f"#list({self.name})"

class IR_ArrayRef(IR_Variable):
    def __init__(self, name:UniqueVariableName, id:int) -> None:
        super().__init__(name)
        self.id = id

    def __str__(self):
        return f"#{self.name}[{self.id}]"

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



class IR_Assign(IR_Symbol, ABC): pass

class IR_SingleAssign(IR_Assign):
    def __init__(self, assign_var: 'IR_Variable', expr: 'IR_Symbol'):
        self.assign_var = assign_var
        self.expr = expr

    def __str__(self) -> str:
        return f"{self.assign_var} = {self.expr}"

class IR_MultiAssign(IR_Assign):
    def __init__(self, assign_vars: List['IR_Variable'], func: str = "TODO"):
        self.assign_vars = assign_vars
        self.func = func

class IR_DefineOnly(IR_Assign):
    def __init__(self, var:'IR_Variable') -> None:
        self.var = var
    
    def __str__(self):
        return f"{self.var}"
