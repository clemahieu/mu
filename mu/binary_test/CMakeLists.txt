cmake_minimum_required (VERSION 2.8)
project (binary_test)

include_directories (${CMAKE_SOURCE_DIR}/gc/include)

add_library (mu_binary_test MODULE
	entry.cpp)