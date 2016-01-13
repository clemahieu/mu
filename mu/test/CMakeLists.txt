cmake_minimum_required (VERSION 2.8)

set (LLVM_LINK_COMPONENTS
  ${LLVM_TARGETS_TO_BUILD}
  ExecutionEngine
  IPO
  MC
  MCJIT)

include_directories (${PROJECT_SOURCE_DIR}/utils/unittest/googletest/include)

add_llvm_tool (mu_test
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
  gtest
  LLVMSupport
  mu_core
  mu_llvmc)