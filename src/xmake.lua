target("cstructures")
    set_kind("static")
    set_targetdir("../temp_libs")
    add_files("*.c") 
    add_includedirs("../include")
    add_cflags("-g -Wall")
    
target("cstruct_iterator")
    set_kind("static")
    set_targetdir("../temp_libs")
    add_files("iterator/*.cpp")
    add_includedirs("../include")
    
