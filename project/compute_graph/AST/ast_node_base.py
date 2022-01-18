import inspect
from typing import Any, Optional

_INDENT=" "

class AST_Node():
    def __pretty_print_val(self, indent_level:int, val: Any)->str:
        if isinstance(val, AST_Node):
            return val.pretty_string(indent_level=indent_level+1)
        else:
            return (_INDENT*indent_level)+str(val)

    def pretty_string(self, indent_level:int=0)->str:
        base_indent = _INDENT*indent_level
        val_indent = _INDENT*(indent_level+1)

        attributes = inspect.getmembers(self, lambda a:not(inspect.isroutine(a)))
        attributes = [a for a in attributes if not(a[0].startswith('__') and a[0].endswith('__'))]

        out_s = f"{base_indent}{type(self).__name__}\n"
        for a,vals in attributes:
            out_s += f"{val_indent}{a}: [\n"
            
            if type(vals) is list:
                for v in vals:
                   out_s += self.__pretty_print_val(indent_level+2, v)
                   out_s += "\n" 
            else:
                out_s += self.__pretty_print_val(indent_level+2, vals)
                out_s += "\n" 
            
            out_s += val_indent+"]\n"

        return out_s





    def __str__(self):
        attributes = inspect.getmembers(self, lambda a:not(inspect.isroutine(a)))
        attributes = [a for a in attributes if not(a[0].startswith('__') and a[0].endswith('__'))]
        return self.pretty_string()
