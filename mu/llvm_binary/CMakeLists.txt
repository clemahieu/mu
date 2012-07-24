cmake_minimum_required (VERSION 2.8)
project (llvm_binary)

include_directories (${CMAKE_SOURCE_DIR}/gc/include)
include_directories (${CMAKE_SOURCE_DIR}/llvm/include)

link_directories (${CMAKE_SOURCE_DIR}/boost/stage/lib)
link_directories (${CMAKE_SOURCE_DIR}/gc/.libs)
if (WIN32)
    link_directories (${CMAKE_SOURCE_DIR}/llvm/lib)
else ()
	link_directories (${CMAKE_SOURCE_DIR}/llvm/Debug+Asserts/lib)
endif ()

add_library (mu_llvm_binary SHARED
	entry.cpp)

target_link_libraries (mu_llvm_binary
    gc
    mu_core
    mu_io
    mu_script
    mu_llvm_)

if (WIN32)
	target_link_libraries (mu_llvm_binary
        LLVM-3.0.dll)
else ()
	target_link_libraries (mu_llvm_binary
        LLVM-3.0)
endif ()
