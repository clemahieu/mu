cmake_minimum_required (VERSION 2.8)
project (llvmc)

include_directories (
    ${llvm_include_directories})
    
link_directories (
    ${llvm_lib_directories})

add_library (mu_llvmc SHARED
	ast.cpp
	ast.hpp
    analyzer.cpp
    analyzer.hpp
    availability.cpp
    availability.hpp
    generator.cpp
    generator.hpp
    node_result.cpp
    node_result.hpp
	parser.cpp
	parser.hpp
    partial_ast.cpp
    partial_ast.hpp
    skeleton.cpp
    skeleton.hpp)
    
target_link_libraries (mu_llvmc
	mu_core
	mu_io
	gc
    LLVM-3.2svn)