from typing import List
from compute_graph.IR.symbols.symbol_base import IR_Symbol, IR_DataTypes
from compute_graph.IR.symbols.variables import IR_Variable, IR_Assign


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


class IR_CallLooseFunction(IR_Symbol):
    def __init__(self, args: List['IR_Variable']):
        self.args = args