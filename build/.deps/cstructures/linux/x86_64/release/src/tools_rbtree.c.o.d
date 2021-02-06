{
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
    files = {
        "src/tools_rbtree.c"
    },
    depfiles_gcc = "build/.objs/cstructures/linux/x86_64/release/src/tools_rbtree.c.o:  src/tools_rbtree.c include/tools_rbtree.h\
"
}