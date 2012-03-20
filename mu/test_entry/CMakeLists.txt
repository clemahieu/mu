cmake_minimum_required (VERSION 2.8)
project (test_entry)

link_directories (${CMAKE_SOURCE_DIR}/boost/stage/lib)
if (WIN32)
	link_directories (${CMAKE_SOURCE_DIR}/llvm/lib)
else ()
	link_directories (${CMAKE_SOURCE_DIR}/llvm/Debug/lib)
endif ()

include_directories (${CMAKE_SOURCE_DIR}/llvm/include)
add_executable (mu_test_entry
	main.cpp)

target_link_libraries (mu_test_entry
	mu_core
	mu_core_test
	mu_io
	mu_io_test
	mu_script
	mu_script_test)

if (NOT WIN32)
	target_link_libraries (mu_test_entry
		boost_filesystem
		boost_system)
endif ()

if (WIN32)
	target_link_libraries (mu_test_entry
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
	target_link_libraries (mu_test_entry
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