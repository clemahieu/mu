cmake_minimum_required (VERSION 2.8)
project (test_entry)

include_directories (
    ${llvm_include_directories}
    ${gtest_include_directories})
    
link_directories (
    ${gtest_lib_directories}
    ${llvm_lib_directories})
    
add_executable (mu_test_entry
	core_directory_iterator_test.cpp
	core_filesystem_test.cpp
	core_list.cpp
    core_node.cpp
    core_node_list_iterator.cpp
	io_complex_identifier.cpp
	io_control.cpp
	io_extension.cpp
	io_extension1.cpp
	io_extension2.cpp
	io_extension3.cpp
	io_extension4.cpp
    io_extension5.cpp
	io_hex_code.cpp
	io_istream_input_test.cpp
    io_analyzer.cpp
    io_analyzer_extensions.cpp
	io_lexer_result.cpp
	io_lexer.cpp
	io_multiline_comment.cpp
        io_scope_global.cpp
        io_scope_block.cpp
	io_source_result.cpp
	io_source.cpp
	io_wistream_input_test.cpp
	llvm_basic_block_insert.cpp
	llvm_basic_block_instruction_insert.cpp
	llvm_constant_string_create.cpp
	llvm_constant_string_extension.cpp
	llvm_function_create.cpp
	llvm_function_type_create.cpp
	llvm_global_variable_create_set.cpp
	llvm_instructions_call.cpp
	llvm_instructions_trunc.cpp
	llvm_linker_link_modules.cpp
	llvm_module_add_package.cpp
	llvm_module_get_package.cpp
    llvm_parser_parser.cpp
    llvm_synthesizer_synthesizer.cpp
	llvm_types_integer.cpp
	main.cpp
    script_abort.cpp
    script_api.cpp
	script_builder.cpp
	script_context.cpp
	script_frame.cpp
	script_chain_operation.cpp
	script_chain_ten_count.cpp
	script_closure_apply.cpp
	script_closure_operation.cpp
	script_closure_single.cpp
	script_debugging_trace_target.cpp
	script_debugging_trace_types.cpp
    script_exec_operation.cpp
	script_integer_equal.cpp
	script_loadb_operation.cpp
	script_loads_operation.cpp
	script_package_create.cpp
	script_package_get_recursive.cpp
	script_package_get.cpp
    script_parser_parser.cpp
    script_parser_scope_merge.cpp
    script_runtime_if_expression.cpp
    script_runtime_while_expression.cpp
	script_string_extension.cpp
    script_synthesizer_synthesizer.cpp
	script_times_operation.cpp
	script_type_check_operation.cpp
    script_vector.cpp)
    
target_link_libraries (mu_test_entry
	gtest
	gc
	LLVM-3.1
	boost_system
	boost_filesystem
	boost_thread
	mu_core
	mu_io
	mu_llvm_
	mu_repl
	mu_script)
