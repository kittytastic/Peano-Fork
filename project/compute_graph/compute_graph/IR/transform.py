from typing import TypeVar, Type
from abc import ABC, abstractmethod
from compute_graph.IR.symbols import IR_Symbol


_T = TypeVar("_T")

class IR_Transfrom(ABC):
    def __init__(self):
        pass

    def assert_and_cast_symbol_type(self, ir:IR_Symbol, subclass:Type[_T])->_T:
        if isinstance(ir, subclass):
            return ir
        else:
            raise Exception(f"Transform: received node type {type(ir).__name__} but expected {type(_T)}")

    @abstractmethod
    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        pass