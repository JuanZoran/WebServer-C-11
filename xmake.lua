set_project("CppServer")
set_languages("cxx17")
set_defaultmode("debug")

if is_mode("debug") then
        add_defines("DEBUG")
        set_symbols("debug")
        set_optimize("none")
        set_warnings("all")
        add_cxxflags("-g")
else
        set_optimize("fastest")
end

target("CppServer")
    set_kind("binary")
    -- 添加头文件搜索路径
    add_includedirs(os.dirs(path.join(os.scriptdir(), "src/*") ))
    add_files("src/main.cpp")
    set_targetdir("bin")



target("test_color")
    set_kind("binary")
    add_includedirs("src/Util")
    add_files("src/Test/test_color.cpp")
