cmake_minimum_required (VERSION 2.8)
project (muc)

add_executable (muc
	entry.cpp)
    
target_link_libraries (muc
    mu_core
    mu_io
    mu_llvmc
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${LLVM_LIBRARIES})