cmake_minimum_required (VERSION 2.8)
project (script_core_binary)

add_library (mu_script_core_binary MODULE
	entry.cpp)
	
target_link_libraries (mu_script_core_binary
	mu_core
	mu_io
	mu_script)