cmake_minimum_required (VERSION 2.8)

add_llvm_library (mu_core
	error.cpp
	error.hpp
	error_string.cpp
	error_string.hpp
    region.cpp
    region.hpp
    siphash24.c
    string_hash.cpp
    string_hash.hpp
    types.cpp
	types.hpp)
