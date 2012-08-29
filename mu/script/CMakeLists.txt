cmake_minimum_required (VERSION 2.8)
project (script)

if (WIN32)
	set (loadb_operation loadb_win32_operation.cpp)
else ()
	set (loadb_operation loadb_unix_operation.cpp)
endif ()

add_library (mu_script SHARED
	api.cpp
    ast_cluster.cpp
    ast_expression.cpp
    ast_parameter.cpp
    ast_reference.cpp
    ast_routine.cpp
	astring_extension.cpp
	astring_node.cpp
	astring_truncate.cpp
	builder.cpp
	bool_c_create.cpp
	bool_c_equal.cpp
	bool_c_node.cpp
	chain_operation.cpp
	closure_apply.cpp
	closure_create.cpp
	closure_create_single.cpp
	closure_hole.cpp
	closure_operation.cpp
	closure_single.cpp
	cluster_node.cpp
	cluster_to_extensions.cpp
    context.cpp
	debugging_trace_error.cpp
	debugging_trace_target.cpp
	debugging_trace_types.cpp
	exec_operation.cpp
	fail_operation.cpp
	frame.cpp
	identity_operation.cpp
	if_c_operation.cpp
	integer_equal.cpp
	integer_extension.cpp
	integer_node.cpp
	integer_subtract.cpp
	${loadb_operation}
	loads_operation.cpp
	location.cpp
	operation.cpp
	package_add.cpp
	package_create.cpp
	package_get.cpp
	package_get_recursive.cpp
	package_node.cpp
	package_remove.cpp
    parser_body.cpp
    parser_cluster.cpp
    parser_error.cpp
    parser_expression.cpp
    parser_parameters.cpp
    parser_parser.cpp
    parser_routine.cpp
	parser_scope_create.cpp
	parser_scope_merge.cpp
	parser_scope_merge_package.cpp
	parser_scope_node.cpp
    parser_state.cpp
    parser_topology.cpp
	print_operation.cpp
	run_operation.cpp
	runtime_expression.cpp
	runtime_fixed.cpp
	runtime_locals.cpp
    runtime_parameter.cpp
	runtime_reference.cpp
	runtime_routine.cpp
	runtime_selection.cpp
	string_extension.cpp
	string_node.cpp
    synthesizer_cluster.cpp
    synthesizer_expression.cpp
    synthesizer_routine.cpp
    synthesizer_synthesizer.cpp
	times_operation.cpp
	type_check_operation.cpp
	unit_operation.cpp
	values_create.cpp
	values_operation.cpp)

if (WIN32)
	target_link_libraries (mu_script
		gc
		boost_system-mgw47-mt-d-1_51
		boost_filesystem-mgw47-mt-d-1_51
		mu_core
		mu_io)
else (WIN32)	
	target_link_libraries (mu_script
		gc
		boost_system
		boost_filesystem
		mu_core
		mu_io)
endif (WIN32)