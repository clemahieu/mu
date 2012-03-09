cmake_minimum_required (VERSION 2.8)
project (script)

if (WIN32)
	set (loadb_operation loadb/win32/operation.cpp)
else ()
	set (loadb_operation loadb/unix/operation.cpp)
endif ()

add_library (mu_script STATIC
	check.cpp
	context.cpp
	fixed.cpp
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
	cluster/get_named.cpp
	cluster/node.cpp
	exec/operation.cpp
	extensions/create.cpp
	extensions/merge.cpp
	extensions/merge_cluster.cpp
	extensions/merge_package.cpp
	extensions/node.cpp
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
	package/create_from_cluster.cpp
	package/get.cpp
	package/get_recursive.cpp
	package/node.cpp
	package/remove.cpp
	print/operation.cpp
	run/operation.cpp
	runtime/call.cpp
	runtime/constant.cpp
	runtime/context.cpp
	runtime/expression.cpp
	runtime/node.cpp
	runtime/parameters.cpp
	runtime/reference.cpp
	runtime/routine.cpp
	runtime/stacktrace_error.cpp
	runtime/trace_registration.cpp
	runtime/trace_target.cpp
	string/extension.cpp
	string/node.cpp
	times/operation.cpp
	type_check/operation.cpp
	unit/operation.cpp
	values/create.cpp
	values/operation.cpp)