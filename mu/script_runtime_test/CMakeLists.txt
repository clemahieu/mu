cmake_minimum_required (VERSION 2.8)
project (script_runtime_test)

add_library (mu_script_runtime_test STATIC
	context.cpp
	tests.cpp)