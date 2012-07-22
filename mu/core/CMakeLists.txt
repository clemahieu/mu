cmake_minimum_required (VERSION 2.8)
project (core)

include_directories (${CMAKE_SOURCE_DIR}/gc/include)

add_library (mu_core STATIC
	apply.cpp
	cluster.cpp
	expression.cpp
	node.cpp
	parameters.cpp
	reference.cpp
	routine.cpp
    visitor.cpp
	errors/error.cpp
	errors/errors.cpp
	errors/error_context.cpp
	errors/error_list.cpp
	errors/error_target.cpp
	errors/string_error.cpp
	errors/null.cpp)