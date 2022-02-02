from typing import Any
from compute_graph.IR.visitor import IR_Visitor
from compute_graph.IR.symbols import *

from pycparser.c_ast import FileAST, FuncDef, ID, Decl, FuncDecl, TypeDecl, ParamList, IdentifierType, PtrDecl # type: ignore
from pycparser import c_generator # type: ignore

NO_OP = ID("no_op") 

class CTF(IR_Visitor[Any]):
    def visit_IR_TightFunction(self, node:IR_TightFunction)->Any:
        #Body -> is compond statement
        #decl -> Decl obj
        #param_decls -> None
        identifier_type = IdentifierType(names=['void'])
        function_type = TypeDecl("FUNCTION_NAME", [], None, identifier_type)
        param_list = ParamList([self.visit(n) for n in node.args])
        func_decl = FuncDecl(param_list, function_type)
        head = Decl("FUNCTION_NAME", [], [], [], [], func_decl, None, None)
        return FuncDef(head, NO_OP, None)

    def visit_IR_LooseFunction(self, node:IR_LooseFunction)->Any:
        raise Exception("Illegal Symbol")

    def visit_IR_ReturnValue(self, node:IR_ReturnValue)->Any:
        raise Exception("Not implemented")

    def visit_IR_NoReturn(self, node:IR_NoReturn)->Any:
        raise Exception("Not implemented")

    def visit_IR_SingleAssign(self, node:IR_SingleAssign)->Any:
        raise Exception("Not implemented")

    def visit_IR_MultiAssign(self, node:IR_MultiAssign)->Any:
        raise Exception("Not implemented")

    def visit_IR_Add(self, node:IR_Add)->Any:
        raise Exception("Not implemented")

    def visit_IR_Sub(self, node:IR_Sub)->Any:
        raise Exception("Not implemented")

    def visit_IR_Mul(self, node:IR_Mul)->Any:
        raise Exception("Not implemented")

    def visit_IR_TempVariable(self, node:IR_TempVariable)->Any:
        raise Exception("Illegal Symbol")

    def visit_IR_SingleVariable(self, node:IR_SingleVariable)->Any:
        raise Exception("Not implemented")
    
    def visit_IR_Array(self, node:IR_Array)->Any:
        raise Exception("Not implemented")

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
            type_dec = TypeDecl(var.name, [], None, id_type) 
            ptr_dec = PtrDecl([], type_dec)
            out_ast = Decl(var.name, [], [], [], [], ptr_dec, None, None)
            return out_ast

        else:
            raise Exception("Not Implemented")

    def visit_IR_ArrayRef(self, node:IR_ArrayRef)->Any:
        raise Exception("Not implemented")

    def visit_IR_CallLooseFunction(self, node:IR_CallLooseFunction)->Any:
        raise Exception("Illegal Symbol")

def compile_as_c(sym: IR_Symbol):
    ast_builder = CTF()
    inner = ast_builder.visit(sym)
    return_ast = FileAST([inner])


    print()
    print("-------- C AST --------")
    return_ast.show(showcoord=False)
    print("------ Generated ------")
    generator:Any = c_generator.CGenerator()
    print(generator.visit(return_ast))

    return return_ast