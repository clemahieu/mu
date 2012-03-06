cmake_minimum_required (VERSION 2.8)
project (binary_test)

add_library (mu_binary_test MODULE
	entry.cpp)
	
target_link_libraries (mu_binary_test
	mu_core
	mu_io
	mu_script)