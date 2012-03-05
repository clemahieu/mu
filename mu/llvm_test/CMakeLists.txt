cmake_minimum_required (VERSION 2.8)
project (llvm_test)

include_directories (${CMAKE_SOURCE_DIR}/llvm/include)
add_library (mu_llvm_test STATIC
	extension.cpp
	instruction_package.cpp
	tests.cpp
	analyzer/operation.cpp
	basic_block/insert.cpp
	ccall/operation.cpp
	constant_string/create.cpp
	constant_string/extension.cpp
	function/create.cpp
	function_type/create.cpp
	global_variable/create_set.cpp
	instructions/call.cpp
	linker/link_modules.cpp
	module/add_package.cpp
	module/get_package.cpp
	types/integer.cpp)