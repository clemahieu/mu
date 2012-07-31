cmake_minimum_required (VERSION 2.8)
project (repl_entry)

add_executable (mu_repl_entry
	main.cpp)

target_link_libraries (mu_repl_entry
    gc
    boost_system
    boost_filesystem
	mu_core
	mu_io
	mu_repl
	mu_script)