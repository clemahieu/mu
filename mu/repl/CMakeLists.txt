cmake_minimum_required (VERSION 2.8)
project (repl)

include_directories (${CMAKE_SOURCE_DIR}/gc/include)

add_library (mu_repl STATIC
	cli_stream.cpp
	data_stream.cpp
	repl.cpp
	quit/operation.cpp)