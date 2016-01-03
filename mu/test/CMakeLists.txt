cmake_minimum_required (VERSION 2.8)
add_custom_target(mu_test)
set_target_properties(mu_test PROPERTIES FOLDER "mu tests")

set (LLVM_LINK_COMPONENTS
  ${LLVM_TARGETS_TO_BUILD}
  ExecutionEngine
  IPO
  MC
  MCJIT)

function(add_mu_unittest test_name)
  add_unittest(mu_test ${test_name} ${ARGN})
  target_link_libraries (${test_name} mu_core mu_io mu_llvmc)
endfunction()

add_mu_unittest (mu_tests
	io_lexer.cpp
	io_stream_istream.cpp
	llvmc_analyzer.cpp
	llvmc_generator.cpp
	llvmc_parser.cpp
	llvmc_skeleton.cpp
	partial_ast.cpp
	literals.cpp)