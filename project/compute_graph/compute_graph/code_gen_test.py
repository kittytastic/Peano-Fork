from typing import Any
from pycparser import parse_file, c_generator # type:ignore
import inspect

def translate_to_c(filename:str):
    """ Simply use the c_generator module to emit a parsed AST.
    """
    ast:Any = parse_file(filename, use_cpp=True)
    ast.show(showcoord=False)

    print()
    print(type(ast))

    print()
    print()
    print("------ Generated ------")
    generator:Any = c_generator.CGenerator()
    print(generator.visit(ast))

    print()
    print()
    inspect_ast(ast.ext[0].body.block_items[5])
    #inspect_ast(ast)


def inspect_ast(node:Any):
    attributes = inspect.getmembers(node, lambda a:not(inspect.isroutine(a)))
    attributes = [a for a in attributes if not(a[0].startswith('__') and a[0].endswith('__'))]

    print(f"INSPECTING: {type(node).__name__}")
    for k,v in attributes:
        print(f"{k}: {v.__repr__()}")

if __name__ == "__main__":
    translate_to_c("./Artifacts/simple.c")
    
