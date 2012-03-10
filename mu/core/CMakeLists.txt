cmake_minimum_required (VERSION 2.8)
project (core)

add_library (mu_core STATIC
	apply.cpp
	cluster.cpp
	context.cpp
	expression.cpp
	node.cpp
	order.cpp
	parameters.cpp
	position.cpp
	reference.cpp
	routine.cpp
    visitor.cpp
	errors/error.cpp
	errors/error_context.cpp
	errors/error_list.cpp
	errors/error_target.cpp
	errors/string_error.cpp)