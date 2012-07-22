cmake_minimum_required (VERSION 2.8)
project (llvm_binary)

include_directories (${CMAKE_SOURCE_DIR}/gc/include)
include_directories (${CMAKE_SOURCE_DIR}/llvm/include)

add_library (mu_llvm_binary MODULE
	entry.cpp)