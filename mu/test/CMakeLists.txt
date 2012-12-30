cmake_minimum_required (VERSION 2.8)
project (test)

include_directories (
	${gtest_include_directories})

link_directories (
	${gtest_lib_directories})

add_executable (mu_test
	io_lexer.cpp
	io_stream_istream.cpp
    llvmc_parser.cpp
	entry.cpp)
    
target_link_libraries (mu_test
	mu_core
	mu_io
	mu_llvmc
	gc
	gtest)