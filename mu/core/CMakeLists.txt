cmake_minimum_required (VERSION 2.8)
project (core)

add_library (mu_core SHARED
	apply.cpp
    check.cpp
	cluster.cpp
    context.cpp
	expression.cpp
    iterator.cpp
	node.cpp
	parameters.cpp
	reference.cpp
	routine.cpp
    visitor.cpp
	errors/error.cpp
	errors/error_context.cpp
	errors/error_list.cpp
	errors/error_target.cpp
	errors/string_error.cpp
	errors/null.cpp)
    
target_link_libraries (mu_core
    gc)