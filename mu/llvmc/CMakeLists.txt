cmake_minimum_required (VERSION 2.8)
project (llvmc)

add_library (mu_llvmc
	ast.cpp
	ast.hpp
    ast_t.hpp
    analyzer.cpp
    analyzer.hpp
    compiler.cpp
    compiler.hpp
    generator.cpp
    generator.hpp
    instruction_type.hpp
    node_result.cpp
    node_result.hpp
	parser.cpp
	parser.hpp
    parser_t.hpp
	predicates.hpp
    skeleton.cpp
    skeleton.hpp
    skeleton_t.hpp)