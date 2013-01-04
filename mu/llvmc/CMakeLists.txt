cmake_minimum_required (VERSION 2.8)
project (llvmc)

add_library (mu_llvmc SHARED
	ast.cpp
	ast.hpp
    availability.cpp
    availability.hpp
    node_result.hpp
	parser.cpp
	parser.hpp
    stream_partial_ast.cpp
    stream_partial_ast.hpp
    wrapper.cpp
    wrapper.hpp)
    
target_link_libraries (mu_llvmc
	mu_core
	mu_io
	gc)