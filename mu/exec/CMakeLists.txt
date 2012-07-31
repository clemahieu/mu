cmake_minimum_required (VERSION 2.8)
project (exec)

add_executable (mu_exec
	main.cpp)

target_link_libraries (mu_exec
    gc
    mu_core
    mu_io
    mu_script
    boost_system
    boost_filesystem)
