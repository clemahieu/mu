cmake_minimum_required (VERSION 2.8)
project (llvm_binary)

link_directories (${CMAKE_SOURCE_DIR}/llvm/lib/Debug)

include_directories (${CMAKE_SOURCE_DIR}/llvm/include)
add_library (mu_llvm_binary MODULE
	entry.cpp)
	
target_link_libraries (mu_llvm_binary
	mu_core
	mu_io
	mu_script
	mu_script_io
	mu_llvm_
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