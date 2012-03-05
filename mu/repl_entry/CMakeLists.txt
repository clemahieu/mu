cmake_minimum_required (VERSION 2.8)
project (repl_entry)

link_directories (${CMAKE_SOURCE_DIR}/boost/stage/lib)

add_executable (mu_repl_entry
	main.cpp)

target_link_libraries (mu_repl_entry
	mu_core
	mu_io
	mu_repl
	mu_script
	mu_script_io)