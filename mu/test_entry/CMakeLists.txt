cmake_minimum_required (VERSION 2.8)
project (test_entry)

include_directories (
    ${llvm_include_directories}
    ${gtest_include_directories})
    
link_directories (
    ${gtest_lib_directories}
    ${llvm_lib_directories})
    
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
    io/extension5.cpp
	io/full.cpp
	io/hex_code.cpp
	io/istream_input_test.cpp
	io/lexer_result.cpp
	io/lexer.cpp
	io/multiline_comment.cpp
    io/name_map.cpp
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
    script/parser/parser.cpp
    script/parser/topology.cpp
	script/string/extension.cpp
	script/synthesizer/operation.cpp
	script/times/operation.cpp
	script/topology/core.cpp
	script/type_check/operation.cpp
	llvm_/extension.cpp
	llvm_/instruction_package.cpp
	llvm_/basic_block/insert.cpp
	llvm_/basic_block/instruction_insert.cpp
	llvm_/basic_block/split_return.cpp
	llvm_/ccall/operation.cpp
	llvm_/constant_string/create.cpp
	llvm_/constant_string/extension.cpp
	llvm_/function/create.cpp
	llvm_/function_type/create.cpp
	llvm_/global_variable/create_set.cpp
	llvm_/instructions/call.cpp
	llvm_/instructions/trunc.cpp
	llvm_/linker/link_modules.cpp
	llvm_/module/add_package.cpp
	llvm_/module/get_package.cpp
	llvm_/synthesizer/operation.cpp
	llvm_/types/integer.cpp)
    
target_link_libraries (mu_test_entry
	gtest
	gc
	LLVM-3.1
	boost_system
	boost_filesystem
	mu_core
	mu_io
	mu_llvm_
	mu_repl
	mu_script)