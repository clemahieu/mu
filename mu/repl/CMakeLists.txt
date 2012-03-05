cmake_minimum_required (VERSION 2.8)
project (repl)

add_library (mu_repl STATIC
	cli_stream.cpp
	data_stream.cpp
	file_stream.cpp
	repl.cpp
	quit/operation.cpp)