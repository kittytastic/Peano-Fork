from typing import Any
from compute_graph.IR.visitor import IR_Visitor
from compute_graph.IR.symbols import *
from compute_graph.code_gen_test import inspect_ast

from pycparser.c_ast import FileAST, FuncDef, ID, Decl, FuncDecl, TypeDecl, ParamList, IdentifierType, PtrDecl, Compound, Assignment, ID, ArrayRef, Constant, BinaryOp # type: ignore
from pycparser import c_generator # type: ignore

NO_OP = ID("no_op") 

class CTF(IR_Visitor[Any]):
    def visit_IR_TightFunction(self, node:IR_TightFunction)->Any:
        function_name = "compute_kernel"

        # Head
        identifier_type = IdentifierType(names=['void'])
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

    def visit_IR_Add(self, node:IR_Add)->Any:
        return BinaryOp("+", self.visit(node.lval), self.visit(node.rval))

    def visit_IR_Sub(self, node:IR_Sub)->Any:
        return BinaryOp("-", self.visit(node.lval), self.visit(node.rval))

    def visit_IR_Mul(self, node:IR_Mul)->Any:
        return BinaryOp("*", self.visit(node.lval), self.visit(node.rval))

    def visit_IR_TempVariable(self, node:IR_TempVariable)->Any:
        raise Exception("Illegal Symbol")

    def visit_IR_SingleVariable(self, node:IR_SingleVariable)->Any:
        return ID(node.name)
    
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
        ss = Constant('int', str(node.id))
        return ArrayRef(ID(node.parent_name), ss)

    def visit_IR_CallLooseFunction(self, node:IR_CallLooseFunction)->Any:
        raise Exception("Illegal Symbol")

def compile_as_c_DEBUG(sym: IR_Symbol):
    ast_builder = CTF()
    inner = ast_builder.visit(sym)
    return_ast = FileAST([inner])

    print()
    print("-------- C AST --------")
    return_ast.show(showcoord=False) # type:ignore
    print("------ Generated ------")
    generator:Any = c_generator.CGenerator()
    print(generator.visit(return_ast))

def compile_as_c(sym: IR_Symbol)->str:
    ast_builder = CTF()
    inner = ast_builder.visit(sym)
    return_ast = FileAST([inner])
    generator:Any = c_generator.CGenerator()

    code = generator.visit(return_ast)
    return code