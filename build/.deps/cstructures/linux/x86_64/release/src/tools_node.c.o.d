{
    files = {
        "src/tools_node.c"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-O3",
            "-Iinclude",
            "-DNDEBUG"
        }
    },
    depfiles_gcc = "build/.objs/cstructures/linux/x86_64/release/src/tools_node.c.o:  src/tools_node.c include/tools_node.h\
"
}