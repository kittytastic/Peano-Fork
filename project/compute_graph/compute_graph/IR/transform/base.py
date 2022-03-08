from typing import Optional, TypeVar, Type, List
from abc import ABC, abstractmethod
from compute_graph.IR.symbols import IR_Symbol
import os.path
import time

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
    def __init__(self, transforms:List[IR_Transfrom], verbose:bool=False, large_output_mode:Optional[str]=None) -> None:
        self.transforms = transforms
        self.verbose = verbose
        self.large_output_mode = large_output_mode

    def safe_large_print(self, msg: str, alias:str):
        if self.large_output_mode:
            with open(os.path.join(self.large_output_mode, f"{alias}.txt"), "w+") as f:
                f.write(msg)
        else:
            print(msg)

    def tf(self, in_IR: IR_Symbol) -> IR_Symbol:
        working_IR = in_IR

        if self.verbose:
            print(f"---------- initial IR -----------")
            self.safe_large_print(str(working_IR), "initial")
            print()


        tc_c = 0
        for tf in self.transforms:
            tc_c += 1
            start = time.time()
            working_IR = tf.tf(working_IR)
            end = time.time()
            if self.verbose:
                print(f"---------- tf {type(tf).__name__} -----------")
                self.safe_large_print(str(working_IR), f"tf-{tc_c}")
                print(f"Elapsed: {end-start:.2f}s")
            
        return working_IR

class FilterApply(IR_Transfrom):
    def __init__(self, filter_type: Type[IR_Symbol], apply_tf:IR_Transfrom):
        self.filter_type = filter_type
        self.apply_tf = apply_tf

    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        expr = in_IR.get_instances(self.filter_type)
        list_expr = list(expr)
        tf_expr = [self.apply_tf.tf(ep) for ep in expr]

        for original, new_expr in zip(list_expr, tf_expr):
            in_IR.replace(original, new_expr)
    
        return in_IR