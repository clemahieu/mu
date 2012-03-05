cmake_minimum_required (VERSION 2.8)
project (test_entry)

link_directories (${CMAKE_SOURCE_DIR}/boost/stage/lib)

add_executable (mu_test_entry
	main.cpp)

target_link_libraries (mu_test_entry
	mu_core
	mu_core_test
	mu_io
	mu_io_test
	mu_repl
	mu_repl_test
	mu_script
	mu_script_test
	mu_script_io
	mu_script_io_test)