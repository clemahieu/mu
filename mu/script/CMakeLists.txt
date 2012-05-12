cmake_minimum_required (VERSION 2.8)
project (script)

if (WIN32)
	set (loadb_operation loadb/win32/operation.cpp)
else ()
	set (loadb_operation loadb/unix/operation.cpp)
endif ()

add_library (mu_script STATIC
	api.cpp
	builder.cpp
	check.cpp
	context.cpp
	frame.cpp
	iterator.cpp
	location.cpp
	operation.cpp
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
	print/operation.cpp
	runtime/expression.cpp
	runtime/fixed.cpp
	runtime/locals.cpp
	runtime/reference.cpp
	runtime/selection.cpp
	runtime/routine.cpp
	run/operation.cpp
	string/extension.cpp
	string/node.cpp
	synthesizer/operation.cpp
	times/operation.cpp
	topology/core.cpp
	topology/node.cpp
	topology/operation.cpp
	type_check/operation.cpp
	unit/operation.cpp
	values/create.cpp
	values/operation.cpp)