cmake_minimum_required (VERSION 2.8)
project (exec)

include_directories (${CMAKE_SOURCE_DIR}/gc/include)

link_directories (${CMAKE_SOURCE_DIR}/boost/stage/lib)
link_directories (${CMAKE_SOURCE_DIR}/gc/.libs)

add_executable (mu_exec
	main.cpp)

target_link_libraries (mu_exec
    gc
    mu_core
    mu_io
    mu_script
    boost_system
    boost_filesystem)
