cmake_minimum_required (VERSION 2.8)

set (LLVM_LINK_COMPONENTS
  ${LLVM_TARGETS_TO_BUILD}
  ExecutionEngine
  IPO
  MC
  MCJIT)

add_llvm_tool (muc
	entry.cpp)

target_link_libraries (muc
  mu_core
  mu_io
  mu_llvmc)