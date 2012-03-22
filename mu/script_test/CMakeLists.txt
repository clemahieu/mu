cmake_minimum_required (VERSION 2.8)
project (script_test)

add_library (mu_script_test STATIC
	tests.cpp
	context.cpp
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
	routine/node.cpp
	string/extension.cpp
	times/operation.cpp
	topology/operation.cpp
	type_check/operation.cpp)