from pycparser import parse_file, c_generator

def translate_to_c(filename:str):
    """ Simply use the c_generator module to emit a parsed AST.
    """
    ast = parse_file(filename, use_cpp=True)
    ast.show(showcoord=False)

    print()
    print(type(ast))

    print()
    print()
    print("------ Generated ------")
    generator = c_generator.CGenerator()
    print(generator.visit(ast))


if __name__ == "__main__":
    translate_to_c("./Artifacts/easiest.c")
    
