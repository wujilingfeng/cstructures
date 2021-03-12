{
    depfiles_gcc = "build/.objs/main/linux/x86_64/release/Demo/main.cpp.o: Demo/main.cpp  include/tools_rbtree.h include/tools_avltree.h  include/tools/tools_int_map.h include/tools/../tools_rbtree.h  include/tools/../iterator/cstruct_iterator.h  include/tools/../iterator/../tools_node.h  include/tools/../iterator/../tools_rbtree.h  include/tools/../iterator/../tools_avltree.h\
",
    files = {
        "Demo/main.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-Iinclude",
            "-I/home/libo/Documents/c++/cstructures/Demo",
            "-I/home/libo/Documents/c++/cstructures/Demo/include",
            "-DNDEBUG"
        }
    }
}