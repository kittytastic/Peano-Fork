from typing import Any, Dict, List, Optional
import datetime
from compute_graph.IR.symbols.functions import IR_BasicLibCall, IR_CallTightFunction, IR_File
from compute_graph.IR.symbols.variables import IR_DefineOnly
from compute_graph.IR.visitor import IR_Visitor
from compute_graph.IR.symbols import *

from pycparser.c_ast import FileAST, FuncDef, ID, Decl, FuncDecl, TypeDecl, ParamList, IdentifierType, PtrDecl, Compound, Assignment, ID, ArrayRef, Constant, BinaryOp, FuncCall, ExprList, ArrayDecl # type: ignore
from pycparser import c_generator # type: ignore

from compute_graph.language_backend.backend_base import LanguageBackend # type: ignore

C_DATA_TYPE_MAP = {IR_DataTypes.VOID: 'void', IR_DataTypes.FP64: 'double'}


_NO_OP = ID("no_op") 
class IR_To_C_TF(IR_Visitor[Any]):
    def __init__(self, data_type_map: Dict[IR_DataTypes, str], function_namespace:Optional[str]):
        self.data_type_map = data_type_map
        self.required_preprocessor_statements:set[str] = set()
        self.function_namespace = function_namespace
        
    def visit_IR_TightFunction(self, node:IR_TightFunction)->Any:
        function_name = node.name
        if self.function_namespace is not None:
            function_name = f"{self.function_namespace}::{function_name}"

        # Head
        identifier_type = IdentifierType(names=[self.data_type_map[node.data_type]])
        function_type = TypeDecl(function_name, [], None, identifier_type)
        param_list = ParamList([self.visit(n) for n in node.args])
        func_decl = FuncDecl(param_list, function_type)
        head = Decl(function_name, [], [], [], [], func_decl, None, None)
        
        # Body
        body_ast = [self.visit(l) for l in node.body]
        body = Compound([n for n in body_ast if n is not None])
        return FuncDef(head, None, body)

    def visit_IR_LooseFunction(self, node:IR_LooseFunction)->Any:
        raise Exception("Illegal Symbol")

    def visit_IR_ReturnValue(self, node:IR_ReturnValue)->Any:
        raise Exception("Not implemented")

    def visit_IR_NoReturn(self, node:IR_NoReturn)->Any:
        return None

    def visit_IR_SingleAssign(self, node:IR_SingleAssign)->Any:
        if isinstance(node.assign_var, IR_VarBodyDefine):
            var = node.assign_var.var
            assert(isinstance(var, IR_SingleVariable)) 
            id_type = IdentifierType(names=["double"])
            type_decl = TypeDecl(var.name, [], [], id_type)
            rhs = self.visit(node.expr)
            return Decl(var.name, [], [], [], [], type_decl, rhs, None)
        elif isinstance(node.assign_var, IR_SingleVariable):
            return Assignment("=", self.visit(node.assign_var), self.visit(node.expr))
        elif isinstance(node.assign_var, IR_ArrayRef):
            return Assignment("=", self.visit(node.assign_var), self.visit(node.expr))
        else:
            raise Exception("Not implemented")

    def visit_IR_MultiAssign(self, node:IR_MultiAssign)->Any:
        raise Exception("Not implemented")
    
    def visit_IR_BasicLibCall(self, node:IR_BasicLibCall)->Any:
        self.required_preprocessor_statements.add(node.header_file)
        return FuncCall(ID(f"{node.namespace}::{node.function_name}"), ExprList([self.visit(var) for var in node.args]))

    def visit_IR_Add(self, node:IR_Add)->Any:
        return BinaryOp("+", self.visit(node.lval), self.visit(node.rval))

    def visit_IR_Sub(self, node:IR_Sub)->Any:
        return BinaryOp("-", self.visit(node.lval), self.visit(node.rval))

    def visit_IR_Mul(self, node:IR_Mul)->Any:
        return BinaryOp("*", self.visit(node.lval), self.visit(node.rval))
    
    def visit_IR_Div(self, node:IR_Div)->Any:
        return BinaryOp("/", self.visit(node.lval), self.visit(node.rval))

    def visit_IR_Const(self, node:IR_Const)->Any:
        return Constant('double', str(node.val))

    def visit_IR_TempVariable(self, node:IR_TempVariable)->Any:
        raise Exception("Illegal Symbol")

    def visit_IR_SingleVariable(self, node:IR_SingleVariable)->Any:
        return ID(node.name)
    
    def visit_IR_Array(self, node:IR_Array)->Any:
        return ID(node.name)

    def visit_IR_VarBodyDefine(self, node:IR_VarBodyDefine)->Any:
        raise Exception("Not implemented")

    def visit_IR_VarArgDefine(self, node:IR_VarArgDefine)->Any:
        # Decl: 2nd arg quals could be ['const']
        var = node.var
        
        if isinstance(var, IR_SingleVariable):
            id_type = IdentifierType(['double'])
            type_dec = TypeDecl(var.name, [], None, id_type) 
            out_ast = Decl(var.name, [], [], [], [], type_dec, None, None)
            return out_ast
        
        elif isinstance(var, IR_Array):
            id_type = IdentifierType(['double'])
            type_dec = TypeDecl(f"@@__restrict__@@{var.name}", [], None, id_type) 
            ptr_dec = PtrDecl([], type_dec)
            out_ast = Decl(f"@@__restrict__@@{var.name}", [], [], [], [], ptr_dec, None, None)
            return out_ast

        else:
            raise Exception("Not Implemented")

    def visit_IR_ArrayRef(self, node:IR_ArrayRef)->Any:
        ss = Constant('int', str(node.id))
        return ArrayRef(ID(node.name), ss)

    def visit_IR_CallLooseFunction(self, node:IR_CallLooseFunction)->Any:
        raise Exception("Illegal Symbol")
    
    def visit_IR_CallTightFunction(self, node:IR_CallTightFunction)->Any:
        return FuncCall(ID(node.function_name), ExprList([self.visit(var.var) for var in node.args])) # type: ignore
    
    def visit_IR_File(self, node:IR_File)->Any:
        return FileAST([self.visit(n) for n in node.body])
    
    def visit_IR_DefineOnly(self, node:IR_DefineOnly)->Any:
        if isinstance(node.var, IR_VarBodyDefine):
            var = node.var.var
            assert(isinstance(var, IR_Array)) 
            id_type = IdentifierType(names=["double"])
            type_decl = TypeDecl(var.name, [], [], id_type)
            array_decl = ArrayDecl(type_decl, Constant('int', str(var.length)), [])
            return Decl(var.name, [], [], [], [], array_decl, None, None)
        else:
            raise Exception("Not implemented")



class C_Backend(LanguageBackend):
    def __init__(self, extra_headers:List[str]=[], namespace:Optional[str]=None) -> None:
        super().__init__()
        self.extra_headers = extra_headers
        self.function_namespace = namespace

    def code_gen(self, ir: IR_Symbol) -> str:
        ast_builder = IR_To_C_TF(C_DATA_TYPE_MAP, self.function_namespace)
        inner = ast_builder.visit(ir)
        return_ast = FileAST([inner])
        generator:Any = c_generator.CGenerator()

        code = generator.visit(return_ast)
        code = code.replace("@@__restrict__@@", "__restrict__ ")
        preproc = "".join([f"#include \"{h}\"\n" for h in self.extra_headers])
        preproc += "\n"
        preproc += "".join([f"#include <{h}>\n" for h in ast_builder.required_preprocessor_statements])

        time_stamp = datetime.datetime.now()

        return f"// Generated: {time_stamp}\n"+preproc+"\n"+code

    def DEBUG_code_gen(self, ir: IR_Symbol)-> str:
        ast_builder = IR_To_C_TF(C_DATA_TYPE_MAP, self.function_namespace)
        inner = ast_builder.visit(ir)
        return_ast = FileAST([inner])

        print()
        print("-------- C AST --------")
        return_ast.show(showcoord=False) # type:ignore
        print("------ Generated ------")
        generator:Any = c_generator.CGenerator()
        code = generator.visit(return_ast)

        return code
    
    def DEBUG_inspect_ast(self, node:Any):
        import inspect
        attributes = inspect.getmembers(node, lambda a:not(inspect.isroutine(a)))
        attributes = [a for a in attributes if not(a[0].startswith('__') and a[0].endswith('__'))]

        print(f"INSPECTING: {type(node).__name__}")
        for k,v in attributes:
            print(f"{k}: {v.__repr__()}")