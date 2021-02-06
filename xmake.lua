add_rules("mode.debug", "mode.release")

includes("src/")
option("demo")
    set_default(true)
    set_showmenu(true)
option("demo_path")
    set_showmenu(true)

if has_config("demo") and has_config("demo_path") then
    target("main")
        add_deps("cstructures","cstruct_iterator")
        set_kind("binary")
        set_targetdir("bin")
        add_files("$(demo_path)/*.cpp")
        add_includedirs("include","$(demo_path)","$(demo_path)/include")
        add_links("cstructures","cstruct_iterator")
        add_linkdirs("temp_libs")

end

-- target("main")
--     add_deps("cstructures","cstruct_iterator")
--     set_kind("binary")
--     set_targetdir("bin")
--     add_files("Demo/*.cpp")
--     add_links("cstructures","cstruct_iterator")
--     add_linkdirs("temp_libs","lib")
--     add_includedirs("include") 
--     on_run(function(target)
--         local file=io.open("src/config.h","w")
--         file:write("libo")
--         file:close()
--     end)
