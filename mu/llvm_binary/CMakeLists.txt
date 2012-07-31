cmake_minimum_required (VERSION 2.8)
project (llvm_binary)

include_directories (
    ${llvm_include_directories})
    
link_directories (
    ${llvm_lib_directories})
    
add_library (mu_llvm_binary SHARED
	entry.cpp)

target_link_libraries (mu_llvm_binary
    gc
    LLVM-3.1
    mu_core
    mu_io
    mu_script
    mu_llvm_)