{
    files = {
        "src/iterator/cstruct_iterator.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-Iinclude",
            "-DNDEBUG"
        }
    },
    depfiles_gcc = "build/.objs/cstruct_iterator/linux/x86_64/release/src/iterator/cstruct_iterator.cpp.o:  src/iterator/cstruct_iterator.cpp include/iterator/cstruct_iterator.h  include/iterator/../tools_node.h include/iterator/../tools_rbtree.h\
"
}