cmake_minimum_required (VERSION 2.8)
project (test)

add_executable (mu_test
	entry.cpp
	io_lexer.cpp
	io_stream_istream.cpp
    llvmc_analyzer.cpp
    llvmc_generator.cpp
    llvmc_parser.cpp
    llvmc_skeleton.cpp
    partial_ast.cpp
    literals.cpp)
    
target_link_libraries (mu_test
	mu_core
	mu_io
	mu_llvmc
	${GTEST_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${LLVM_LIBRARIES})