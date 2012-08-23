cmake_minimum_required (VERSION 2.8)
project (script)

if (WIN32)
	set (loadb_operation loadb/win32/operation.cpp)
else ()
	set (loadb_operation loadb/unix/operation.cpp)
endif ()

add_library (mu_script SHARED
	api.cpp
    ast_cluster.cpp
    ast_expression.cpp
    ast_parameter.cpp
    ast_reference.cpp
    ast_routine.cpp
	builder.cpp
    context.cpp
	frame.cpp
	location.cpp
	operation.cpp
    synthesizer_cluster.cpp
    synthesizer_expression.cpp
    synthesizer_routine.cpp
    synthesizer_synthesizer.cpp
	analyzer/operation.cpp
	ast/extension.cpp
	ast/merge.cpp
	ast/read_from_file.cpp
	astring/extension.cpp
	astring/node.cpp
	astring/truncate.cpp
	bool_c/create.cpp
	bool_c/equal.cpp
	bool_c/node.cpp
	chain/operation.cpp
	closure/apply.cpp
	closure/create.cpp
	closure/create_single.cpp
	closure/hole.cpp
	closure/operation.cpp
	closure/single.cpp
	cluster/node.cpp
	cluster/remap.cpp
	cluster/remap_node.cpp
	debugging/trace_error.cpp
	debugging/trace_target.cpp
	debugging/trace_types.cpp
	exec/operation.cpp
	extensions/create.cpp
	extensions/merge.cpp
	extensions/merge_package.cpp
	extensions/node.cpp
	fail/operation.cpp
	identity/operation.cpp
	if_c/operation.cpp
	integer/equal.cpp
	integer/extension.cpp
	integer/node.cpp
	integer/subtract.cpp
	load/operation.cpp
	${loadb_operation}
	loads/operation.cpp
	package/add.cpp
	package/create.cpp
	package/get.cpp
	package/get_recursive.cpp
	package/node.cpp
	package/remove.cpp
    parser/body.cpp
    parser/cluster.cpp
    parser/error.cpp
    parser/expression.cpp
    parser/parameters.cpp
    parser/parser.cpp
    parser/routine.cpp
    parser/state.cpp
    parser/topology.cpp
	print/operation.cpp
	runtime/expression.cpp
	runtime/fixed.cpp
	runtime/locals.cpp
    runtime/parameter.cpp
	runtime/reference.cpp
	runtime/routine.cpp
	runtime/selection.cpp
	run/operation.cpp
	string/extension.cpp
	string/node.cpp
	times/operation.cpp
	topology/core.cpp
	topology/node.cpp
	topology/operation.cpp
	type_check/operation.cpp
	unit/operation.cpp
	values/create.cpp
	values/operation.cpp)

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