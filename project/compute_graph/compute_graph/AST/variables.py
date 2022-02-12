from typing import List, Optional
from abc import ABC, abstractmethod
from compute_graph.AST import AST_Node, AST_Assign, AST_DecVariable, AST_GetVariable

class Variable(ABC):
    references:List['VariableReference'] = []
    def __init__(self, id:str) -> None:
        self.id = id

    @abstractmethod
    def declare(self)->Optional[AST_Node]:
        pass

    def get_references(self)->List['VariableReference']:
        return self.references

class VariableReference(ABC):
    def __init__(self, var: Variable) -> None:
        self.var = var

    @abstractmethod
    def set(self, expr:AST_Node)->AST_Node:
        pass

    @abstractmethod
    def ref(self)->AST_Node:
        pass


class LocalVar(Variable):
    def __init__(self, id: str) -> None:
        self.references = [LocalVarRef(self)]
        super().__init__(id)

    def declare(self)->AST_Node:
        return AST_DecVariable(self.id)

class LocalVarRef(VariableReference):
    def __init__(self, var: Variable) -> None:
        super().__init__(var)

    def set(self, expr: AST_Node) -> AST_Node:
        return AST_Assign(AST_GetVariable(self.var.id), expr)

    def ref(self)->AST_Node:
        return AST_GetVariable(self.var.id)
