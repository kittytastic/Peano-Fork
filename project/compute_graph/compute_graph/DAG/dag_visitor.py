from typing import Callable, TypeVar, Generic
from abc import ABC, abstractmethod
from compute_graph.DAG.graph import Graph

from compute_graph.DAG.node import DAG_Node
from compute_graph.DAG.ops import Add, Multiply, Subtract
from compute_graph.DAG.primitive_node import InputPassThrough, PassThroughNode, TerminalInput

_NOT_IMPLEMENTED = "Visitor method not implemented"

_S = TypeVar("_S")
_T = TypeVar("_T")

class DAG_Visitor(Generic[_T], ABC):
    def visit(self, node:DAG_Node)->_T:
        node_type = type(node).__name__
        visit_func_name = f"visit{node_type}"

        if not hasattr(self, visit_func_name):
            raise Exception(f"No visitor function found for node type: {node_type}  (looking for function: {visit_func_name}")
        
        visit_func: Callable[[DAG_Node], _T] = getattr(self, visit_func_name)
        return visit_func(node)

    @abstractmethod
    def visitGraph(self, node:Graph)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)
    
    # Ops
    @abstractmethod
    def visitAdd(self, node:Add)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)
    
    @abstractmethod
    def visitSubtract(self, node:Subtract)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)
    
    @abstractmethod
    def visitMultiply(self, node:Multiply)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)
    
    @abstractmethod
    def visitTerminalInput(self, node:TerminalInput)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)
    
    @abstractmethod
    def visitPassThroughNode(self, node:PassThroughNode)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)
    
    @abstractmethod
    def visitInputPassThrough(self, node:InputPassThrough)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)


class DAG_PropsVisitor(Generic[_T, _S], ABC):
    def visit(self, node:DAG_Node, props: _S)->_T:
        node_type = type(node).__name__
        visit_func_name = f"visit{node_type}"

        if not hasattr(self, visit_func_name):
            raise Exception(f"No visitor function found for node type: {node_type}  (looking for function: {visit_func_name}")
        
        visit_func: Callable[[DAG_Node, _S], _T] = getattr(self, visit_func_name)
        return visit_func(node, props)

    @abstractmethod
    def visitGraph(self, node:Graph, props: _S)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)
    
    # Ops
    @abstractmethod
    def visitAdd(self, node:Add, props: _S)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)
    
    @abstractmethod
    def visitSubtract(self, node:Subtract, props:_S)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)
    
    @abstractmethod
    def visitMultiply(self, node:Multiply, props: _S)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)
    
    @abstractmethod
    def visitTerminalInput(self, node:TerminalInput, props:_S)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)
    
    @abstractmethod
    def visitPassThroughNode(self, node:PassThroughNode, props:_S)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)
    
    @abstractmethod
    def visitInputPassThrough(self, node:InputPassThrough, props:_S)->_T:
        raise NotImplementedError(_NOT_IMPLEMENTED)


class BasicDagVisitor(DAG_Visitor[str]):
    def visitGraph(self, node:Graph)->str:
        child_nodes = node.get_sub_nodes()
        child_node_visit = [self.visit(n) for n in child_nodes]
        child_node_str = "\n\t".join(child_node_visit)
        return f"Graph:\n\t{child_node_str}"

    def visitAdd(self, node:Add)->str:
        return "Add"
    
    def visitSubtract(self, node:Subtract)->str:
        return "Subtract"
    
    def visitMultiply(self, node:Multiply)->str:
        return "Multiply"
    
    def visitTerminalInput(self, node:TerminalInput)->str:
        return "Terminal Input"
    
    def visitPassThroughNode(self, node:PassThroughNode)->str:
        return "Pass Through"
    
    def visitInputPassThrough(self, node:InputPassThrough)->str:
        return "Input Pass Through"


