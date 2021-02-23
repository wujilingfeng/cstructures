{
    depfiles_gcc = "build/.objs/cstructures/linux/x86_64/release/src/tools_avltree.c.o:  src/tools_avltree.c include/tools_avltree.h\
",
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
        "src/tools_avltree.c"
    }
}