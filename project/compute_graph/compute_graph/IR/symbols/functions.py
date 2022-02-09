from typing import List
from compute_graph.IR.symbols.symbol_base import IR_Symbol, IR_DataTypes
from compute_graph.IR.symbols.variables import IR_Variable, IR_Assign

class IR_File(IR_Symbol):
    def __init__(self, body: List[IR_Symbol]) -> None:
        self.body = body
    
    def __str__(self):
        return "\n\n".join([str(b) for b in self.body])

class IR_LooseFunction(IR_Symbol):
    def __init__(self, data_type:IR_DataTypes, in_var: List['IR_Variable'], out_var: List['IR_Variable'], body: List['IR_Assign'], name:str):
        self.data_type = data_type
        self.in_var = in_var
        self.out_var = out_var
        self.body = body
        self.name = name
    
    def __str__(self):
        in_var_str = ", ".join([str(iv) for iv in self.in_var])
        out_var_str = ", ".join([str(iv) for iv in self.out_var])
        body_str = "\n\t".join([str(b) for b in self.body])
        out_str = f"define {self.data_type} @{self.name} ({in_var_str}) ({out_var_str}):\n\t{body_str}"
        return out_str

class IR_TightFunction(IR_Symbol):
    def __init__(self, data_type:IR_DataTypes, args: List['IR_Variable'], body: List['IR_Assign'], return_statement: 'IR_Return', name:str):
        self.data_type = data_type
        self.args = args
        self.body = body
        self.return_statement = return_statement
        self.name = name
    
    def __str__(self):
        arg_str = ", ".join([str(a) for a in self.args])
        body_str = "\n\t".join([str(b) for b in self.body])
        out_str = f"define {self.data_type} @{self.name} ({arg_str}):\n\t{body_str}\n\t{str(self.return_statement)}"
        return out_str   

class IR_Return(IR_Symbol): pass
class IR_ReturnValue(IR_Return):
    def __str__(self) -> str:
        return "<return something>"

class IR_NoReturn(IR_Return):
    def __str__(self) -> str:
        return "<return nothing>"


class IR_CallLooseFunction(IR_Assign):
    def __init__(self, function_name: str, inputs: List['IR_Variable'], outputs: List['IR_Variable']):
        self.function_name = function_name
        self.inputs = inputs
        self.outputs = outputs

    def __str__(self):
        input_args = ", ".join([str(i) for i in self.inputs])
        output_args = ", ".join([str(o) for o in self.outputs])
        return f"call @{self.function_name}  in: ({input_args})  out: ({output_args})"

class IR_CallTightFunction(IR_Assign):
    def __init__(self, function_name: str, args: List['IR_Variable']):
        self.function_name = function_name
        self.args = args

    def __str__(self):
        args = ", ".join([str(i) for i in self.args])
        return f"call @{self.function_name} ({args})"