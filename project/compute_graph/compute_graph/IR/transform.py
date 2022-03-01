from typing import TypeVar, Type, List
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
            raise Exception(f"Transform: received node type {type(ir).__name__} but expected {subclass.__name__}")

    @abstractmethod
    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        pass

class IR_TransformChain(IR_Transfrom):
    def __init__(self, transforms:List[IR_Transfrom], verbose:bool=False) -> None:
        self.transforms = transforms
        self.verbose = verbose


    def tf(self, in_IR: IR_Symbol) -> IR_Symbol:
        working_IR = in_IR

        if self.verbose:
            print(f"---------- initial IR -----------")
            print(working_IR)
            print()

        for tf in self.transforms:
            working_IR = tf.tf(working_IR)
            if self.verbose:
                print(f"---------- tf {type(tf).__name__} -----------")
                print(working_IR)
                print()
            
        return working_IR