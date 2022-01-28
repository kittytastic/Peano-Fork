from typing import List
from compute_graph.DAG.dag_visitor import DAG_PropsVisitor
from compute_graph.DAG import Graph, Add, Subtract, Multiply, TerminalInput, PassThroughNode, InputPassThrough

from compute_graph.AST import AST_Node, AST_Add, AST_Sub, AST_Mul

class DAGToASTVisitor(DAG_PropsVisitor[List[AST_Node], List[AST_Node]]):
    def visitGraph(self, node:Graph, props: List[AST_Node])->List[AST_Node]:
       raise Exception("Not supported") 

    def visitAdd(self, node:Add, props: List[AST_Node])->List[AST_Node]:
        return [AST_Add(props[0], props[1])]
    
    def visitSubtract(self, node:Subtract, props: List[AST_Node])->List[AST_Node]:
        return [AST_Sub(props[0], props[1])]
    
    def visitMultiply(self, node:Multiply, props: List[AST_Node])->List[AST_Node]:
        return [AST_Mul(props[0], props[1])]
    
    def visitTerminalInput(self, node:TerminalInput, props: List[AST_Node])->List[AST_Node]:
        raise Exception("Not implemented")
    
    def visitPassThroughNode(self, node:PassThroughNode, props: List[AST_Node])->List[AST_Node]:
        return props
    
    def visitInputPassThrough(self, node:InputPassThrough, props: List[AST_Node])->List[AST_Node]:
        return props