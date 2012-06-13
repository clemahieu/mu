cmake_minimum_required (VERSION 2.8)
project (test_entry)

link_directories (${CMAKE_SOURCE_DIR}/boost/stage/lib)
if (WIN32)
	link_directories (${CMAKE_SOURCE_DIR}/llvm/lib)
else ()
	link_directories (${CMAKE_SOURCE_DIR}/llvm/Debug/lib)
endif ()

link_directories (${CMAKE_SOURCE_DIR}/googletest)

include_directories (${CMAKE_SOURCE_DIR}/llvm/include)
add_executable (mu_test_entry
	main.cpp
	core/apply.cpp
	core/directory_iterator_test.cpp
	core/filesystem_test.cpp
	core/list.cpp
	core/segment.cpp
	core/test_visitor.cpp
	core/visitor.cpp
	io/analyzer_result.cpp
	io/analyzer.cpp
	io/begin.cpp
	io/builder.cpp
	io/complex_identifier.cpp
	io/control.cpp
	io/extension.cpp
	io/extension1.cpp
	io/extension2.cpp
	io/extension3.cpp
	io/extension4.cpp
	io/full.cpp
	io/hex_code.cpp
	io/istream_input_test.cpp
	io/lexer_result.cpp
	io/lexer.cpp
	io/multiline_comment.cpp
	io/parser_result.cpp
	io/parser.cpp
	io/routine.cpp
	io/single.cpp
	io/source_result.cpp
	io/source.cpp
	io/values.cpp
	io/wistream_input_test.cpp
	script/builder.cpp
	script/context.cpp
	script/frame.cpp
	script/analyzer/operation.cpp
	script/ast/extension.cpp
	script/chain/operation.cpp
	script/chain/ten_count.cpp
	script/closure/apply.cpp
	script/closure/operation.cpp
	script/closure/single.cpp
	script/cluster/remap.cpp
	script/debugging/trace_target.cpp
	script/debugging/trace_types.cpp
	script/integer/equal.cpp
	script/loadb/operation.cpp
	script/loads/operation.cpp
	script/package/create.cpp
	script/package/get_recursive.cpp
	script/package/get.cpp
	script/string/extension.cpp
	script/synthesizer/operation.cpp
	script/times/operation.cpp
	script/topology/core.cpp
	script/type_check/operation.cpp)
    
target_link_libraries (mu_test_entry
    gtest)

target_link_libraries (mu_test_entry
	mu_core
	mu_io
	mu_llvm_
	mu_llvm_test
	mu_repl
	mu_repl_test
	mu_script)

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