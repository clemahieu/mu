cmake_minimum_required (VERSION 2.8)
project (script_test)

add_library (mu_script_test STATIC
	call.cpp
	constant.cpp
	expression.cpp
	reference.cpp
	routine.cpp
	tests.cpp
	analyzer/operation.cpp
	ast/extension.cpp
	chain/operation.cpp
	chain/ten_count.cpp
	closure/apply.cpp
	closure/operation.cpp
	closure/single.cpp
	integer/equal.cpp
	loadb/operation.cpp
	loads/operation.cpp
	package/create.cpp
	package/get.cpp
	package/get_recursive.cpp
	runtime/trace_target.cpp
	string/extension.cpp
	times/operation.cpp
	type_check/operation.cpp)