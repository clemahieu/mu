cmake_minimum_required (VERSION 2.8)
project (llvm_binary)

include_directories (${CMAKE_SOURCE_DIR}/gc/include)

link_directories (${CMAKE_SOURCE_DIR}/gc/.libs)

if (WIN32)
	link_directories (${CMAKE_SOURCE_DIR}/llvm/lib)
else ()
	link_directories (${CMAKE_SOURCE_DIR}/llvm/Debug/lib)
endif ()

include_directories (${CMAKE_SOURCE_DIR}/llvm/include)
add_library (mu_llvm_binary MODULE
	entry.cpp)
	
target_link_libraries (mu_llvm_binary
	mu_core
	mu_io
	mu_script
	mu_llvm_)

if (WIN32)
	target_link_libraries (mu_llvm_binary
	        LLVMCore.lib
        	LLVMSupport.lib
	        LLVMExecutionEngine.lib
	        LLVMTarget.lib
	        LLVMJIT.lib
	        LLVMMC.lib
	        LLVMCodeGen.lib
	        LLVMAnalysis.lib
	        LLVMX86Info.lib
        	LLVMTransformUtils.lib
	        LLVMX86CodeGen.lib
        	LLVMSelectionDAG.lib
	        LLVMX86Utils.lib
        	LLVMScalarOpts.lib
	        LLVMX86Desc.lib
        	LLVMAsmParser.lib
	        LLVMLinker.lib
        	LLVMX86AsmPrinter.lib
	        LLVMAsmPrinter.lib
        	LLVMMCParser.lib)
else ()
	target_link_libraries (mu_llvm_binary
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
endif ()

target_link_libraries (mu_llvm_binary
    gc)