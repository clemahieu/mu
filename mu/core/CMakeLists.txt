cmake_minimum_required (VERSION 2.8)
project (core)

add_library (mu_core SHARED
    check.cpp
    context.cpp
    iterator.cpp
	node.cpp
    node_list.cpp
    node_list_iterator.cpp
	errors/error.cpp
	errors/error_context.cpp
	errors/error_list.cpp
	errors/error_target.cpp
	errors/string_error.cpp
	errors/null.cpp)
    
target_link_libraries (mu_core
    gc)