cmake_minimum_required (VERSION 2.8)
project (muc)

include_directories (
    ${llvm_include_directories})

link_directories (
    ${llvm_lib_directories}
    ${boost_lib_directories})

add_executable (muc
    compiler.cpp
    compiler.hpp
	entry.cpp)
    
target_link_libraries (muc
    mu_core
    mu_io
    mu_llvmc
    boost_filesystem
    boost_program_options
    boost_system)