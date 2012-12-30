cmake_minimum_required (VERSION 2.8)
project (llvmc)

add_library (mu_llvmc SHARED
	ast.cpp
	ast.hpp
    availability.cpp
    availability.hpp
	parser.cpp
	parser.hpp)
    
target_link_libraries (mu_llvmc
	mu_core
	mu_io
	gc)