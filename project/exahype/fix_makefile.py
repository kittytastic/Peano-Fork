import sys

if __name__=="__main__":
    assert(len(sys.argv)>=2)
    insert_args = sys.argv[1:]

    print(f"Inserting {insert_args} into CXX_SOURCES")

    replacement_cxx_sources = "CXX_SOURCES="+" ".join(insert_args)+" "
    with open("Makefile", "r") as f:
        make_file = f.read()
        if replacement_cxx_sources not in make_file:
            new_mf = make_file.replace("CXX_SOURCES=", replacement_cxx_sources)
        else:
            new_mf = make_file
            print("Skipped, already in sources")

    
    with open("Makefile", "w") as f:
        f.write(new_mf)
