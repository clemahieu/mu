cmake_minimum_required (VERSION 2.8)
project (llvm_binary)

include_directories (${CMAKE_SOURCE_DIR}/gc/include)
include_directories (${CMAKE_SOURCE_DIR}/llvm/include)

link_directories (${CMAKE_SOURCE_DIR}/gc/.libs)
if (WIN32)
        link_directories (${CMAKE_SOURCE_DIR}/llvm/lib)
else ()
        link_directories (${CMAKE_SOURCE_DIR}/llvm/Debug/lib)
endif ()

add_library (mu_llvm_binary SHARED
	entry.cpp)

target_link_libraries (mu_llvm_binary
    gc
    mu_core
    mu_io
    mu_script
    mu_llvm_
    LLVMCore
    LLVMSupport
    LLVMExecutionEngine
    LLVMTarget
    LLVMJIT
    LLVMMC
    LLVMCodeGen
    LLVMAnalysis
    LLVMX86Info
    LLVMTransformUtils
    LLVMX86CodeGen
    LLVMSelectionDAG
    LLVMX86Utils
    LLVMScalarOpts
    LLVMX86Desc
    LLVMAsmParser
    LLVMLinker
    LLVMX86AsmPrinter
    LLVMAsmPrinter
    LLVMMCParser)
