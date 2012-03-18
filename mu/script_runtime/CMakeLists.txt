cmake_minimum_required (VERSION 2.8)
project (script_runtime)

add_library (mu_script_runtime STATIC
	context.cpp
	location.cpp
	operation.cpp)