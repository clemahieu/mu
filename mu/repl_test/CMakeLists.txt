cmake_minimum_required (VERSION 2.8)
project (repl_test)

add_library (mu_repl_test STATIC
	api_test.cpp
	file_stream_test.cpp
	tests.cpp)