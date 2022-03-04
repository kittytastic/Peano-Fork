from abc import ABC, abstractmethod
from typing import  TypeVar, Generic, Callable 
from compute_graph.IR.symbols import *
from compute_graph.IR.symbols.functions import IR_BasicLibCall, IR_CallTightFunction, IR_File
from compute_graph.IR.symbols.variables import IR_DefineOnly 

_T = TypeVar("_T") # type:ignore

class IR_Visitor(Generic[_T], ABC):
    def visit(self, node:IR_Symbol)->_T:
        node_type = type(node).__name__
        visit_func_name = f"visit_{node_type}"

        if not hasattr(self, visit_func_name):
            raise Exception(f"No visitor function found for node type: {node_type}  (looking for function: {visit_func_name}")
        
        visit_func: Callable[[IR_Symbol], _T] = getattr(self, visit_func_name)
        return visit_func(node)

    def visit_IR_Symbol(self, node:IR_Symbol)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_TightFunction(self, node:IR_TightFunction)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_LooseFunction(self, node:IR_LooseFunction)->_T:
        raise Exception("Not implemented")

    def visit_IR_Return(self, node:IR_Return)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_ReturnValue(self, node:IR_ReturnValue)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_NoReturn(self, node:IR_NoReturn)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_BasicLibCall(self, node:IR_BasicLibCall)->_T:
        raise Exception("Not implemented")
    
    def visit_IR_Assign(self, node:IR_Assign)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_SingleAssign(self, node:IR_SingleAssign)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_MultiAssign(self, node:IR_MultiAssign)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_Add(self, node:IR_Add)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_Sub(self, node:IR_Sub)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_Mul(self, node:IR_Mul)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_Div(self, node:IR_Div)->_T:
        raise Exception("Not implemented")
    
    @abstractmethod
    def visit_IR_Const(self, node:IR_Const)->_T:
        raise Exception("Not implemented")
    
    def visit_IR_Variable(self, node:IR_Variable)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_TempVariable(self, node:IR_TempVariable)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_SingleVariable(self, node:IR_SingleVariable)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_Array(self, node:IR_Array)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_VarBodyDefine(self, node:IR_VarBodyDefine)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_VarArgDefine(self, node:IR_VarArgDefine)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_ArrayRef(self, node:IR_ArrayRef)->_T:
        raise Exception("Not implemented")

    @abstractmethod
    def visit_IR_CallLooseFunction(self, node:IR_CallLooseFunction)->_T:
        raise Exception("Not implemented")
    
    @abstractmethod
    def visit_IR_CallTightFunction(self, node:IR_CallTightFunction)->_T:
        raise Exception("Not implemented")
    
    @abstractmethod
    def visit_IR_File(self, node:IR_File)->_T:
        raise Exception("Not implemented")
    
    @abstractmethod
    def visit_IR_DefineOnly(self, node:IR_DefineOnly)->_T:
        raise Exception("Not implemented")