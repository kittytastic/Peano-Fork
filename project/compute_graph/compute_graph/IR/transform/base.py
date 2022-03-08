from typing import Optional, Tuple, TypeVar, Type, List
from abc import ABC, abstractmethod
from compute_graph.IR.symbols import IR_Symbol
import os.path
import time

from compute_graph.IR.symbols.functions import IR_File

_T = TypeVar("_T")

class IR_Transfrom(ABC):
    def __init__(self, name:Optional[str]=None):
        self.name = type(self).__name__ if name is None else name

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
        super().__init__()
        self.transforms = transforms
        self.verbose = verbose
        self.large_output_mode = large_output_mode

    def safe_large_print(self, msg: str, alias:str):
        if self.large_output_mode:
            with open(os.path.join(self.large_output_mode, f"{alias}.txt"), "w+") as f:
                f.write(msg)
        else:
            print(msg)

    def _stats(self, in_IR: IR_File)->Tuple[int, int]:
        functions_c = len(in_IR.body)
        line_c = sum([len(f.body) for f in in_IR.body]) #type: ignore
        return functions_c, line_c

    def tf(self, in_IR: IR_Symbol) -> IR_Symbol:
        working_IR = in_IR

        if self.verbose:
            self.safe_large_print(str(working_IR), "initial")
            
            outS = f"Initial IR: "
            if isinstance(in_IR, IR_File):
                stats = self._stats(in_IR)
                outS += (f" {stats[0]} functions  {stats[1]} lines")
            print(outS)


        tc_c = 0
        for tf in self.transforms:
            tc_c += 1
            start = time.time()
            working_IR = tf.tf(working_IR)
            end = time.time()
            if self.verbose:
                outS = f"({end-start:.2f}s) {tf.name}: "
                if isinstance(working_IR, IR_File):
                    stats = self._stats(working_IR)
                    outS += (f" {stats[0]} functions  {stats[1]} lines")
                print(outS)
                self.safe_large_print(str(working_IR), f"tf-{tc_c}")
            
        return working_IR

class FilterApply(IR_Transfrom):
    def __init__(self, filter_type: Type[IR_Symbol], apply_tf:IR_Transfrom):
        super().__init__(name=type(apply_tf).__name__)
        self.filter_type = filter_type
        self.apply_tf = apply_tf

    def tf(self, in_IR: IR_Symbol)->IR_Symbol:
        expr = in_IR.get_instances(self.filter_type)
        list_expr = list(expr)
        tf_expr = [self.apply_tf.tf(ep) for ep in expr]

        for original, new_expr in zip(list_expr, tf_expr):
            in_IR.replace(original, new_expr)
    
        return in_IR