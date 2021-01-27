add_rules("mode.debug", "mode.release")

includes("src/")

-- target("cstructures")
--     set_kind("static")
--     set_targetdir
---add_configfiles("src/config.h.in")

target("main")
    add_deps("cstructures","cstruct_iterator")
    set_kind("binary")
    set_targetdir("bin")
    add_files("Demo/*.cpp")
    add_links("cstructures","cstruct_iterator")
    add_linkdirs("temp_libs","lib")
    add_includedirs("include") 
    on_run(function(target)
        local file=io.open("src/config.h","w")
        file:write("libo")
        file:close()
    end)
