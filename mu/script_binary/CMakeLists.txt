cmake_minimum_required (VERSION 2.8)
project (script_binary)

link_directories (${CMAKE_SOURCE_DIR}/boost/stage/lib)
link_directories (${CMAKE_SOURCE_DIR}/gc/.libs)

add_library (mu_script_binary MODULE
	entry.cpp)

target_link_libraries (mu_script_binary
    gc
    mu_core
    mu_io
    mu_script
    boost_system
    boost_filesystem)
