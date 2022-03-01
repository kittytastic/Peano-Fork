from compute_graph.IR.symbols.symbol_base import IR_Symbol

class IR_Add(IR_Symbol):
    def __init__(self, lval: IR_Symbol, rval: IR_Symbol):
        self.lval = lval
        self.rval = rval
    
    def __str__(self):
        return f"{self.lval} + {self.rval}"

class IR_Sub(IR_Symbol):
    def __init__(self, lval: IR_Symbol, rval: IR_Symbol):
        self.lval = lval
        self.rval = rval

    def __str__(self):
        return f"{self.lval} - {self.rval}"

class IR_Mul(IR_Symbol):
    def __init__(self, lval: IR_Symbol, rval: IR_Symbol):
        self.lval = lval
        self.rval = rval
    
    def __str__(self):
        return f"{self.lval} * {self.rval}"

class IR_Div(IR_Symbol):
    def __init__(self, lval: IR_Symbol, rval: IR_Symbol):
        self.lval = lval
        self.rval = rval
    
    def __str__(self):
        return f"{self.lval} / {self.rval}"
