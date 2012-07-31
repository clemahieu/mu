cmake_minimum_required (VERSION 2.8)
project (script_core_binary)

add_library (mu_script_core_binary SHARED
	entry.cpp)

target_link_libraries (mu_script_core_binary
    gc
    mu_core
    mu_io
    mu_script
    boost_system
    boost_filesystem)
