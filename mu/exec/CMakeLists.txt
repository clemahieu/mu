cmake_minimum_required (VERSION 2.8)
project (exec)

include_directories (${CMAKE_SOURCE_DIR}/gc/include)

add_executable (mu_exec
	main.cpp)