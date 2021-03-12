{
    files = {
        "build/.objs/main/linux/x86_64/release/Demo/main.cpp.o",
        "temp_libs/libcstructures.a",
        "temp_libs/libcstruct_iterator.a"
    },
    values = {
        "/usr/bin/g++",
        {
            "-m64",
            "-Ltemp_libs",
            "-s",
            "-lcstruct_iterator",
            "-lcstructures"
        }
    }
}