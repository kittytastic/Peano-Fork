from compute_graph.IR.transform.base import IR_Transfrom
from compute_graph.IR.symbols import IR_Symbol


class IR_TF_STOP(IR_Transfrom):
    def __init__(self):
        super().__init__()
    
    def tf(self, in_IR: IR_Symbol) -> IR_Symbol:
        exit()