{
    files = {
        "src/tools_rbtree.c"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-O3",
            "-Iinclude",
            "-g",
            "-Wall",
            "-DNDEBUG"
        }
    },
    depfiles_gcc = "build/.objs/cstructures/linux/x86_64/release/src/tools_rbtree.c.o:  src/tools_rbtree.c include/tools_rbtree.h\
"
}