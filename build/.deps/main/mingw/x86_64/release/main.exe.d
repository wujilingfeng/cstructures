{
    files = {
        [[build\.objs\main\mingw\x86_64\release\Demo\main.cpp.obj]],
        [[temp_libs\cstructures.lib]],
        [[temp_libs\cstruct_iterator.lib]]
    },
    values = {
        [[C:\Program Files\Haskell Platform\8.6.5\mingw\bin\x86_64-w64-mingw32-g++]],
        {
            "-m64",
            "-Ltemp_libs",
            "-s",
            "-lcstruct_iterator",
            "-lcstructures"
        }
    }
}