from abc import ABC, abstractmethod
from compute_graph.IR.symbols import IR_Symbol

class LanguageBackend(ABC):
    @abstractmethod
    def code_gen(self, ir: IR_Symbol)->str:
        raise Exception("Not implemented")