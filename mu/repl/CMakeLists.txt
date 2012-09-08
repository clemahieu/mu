cmake_minimum_required (VERSION 2.8)
project (repl)

add_library (mu_repl SHARED
    api.cpp
	cli_stream.cpp
	data_stream.cpp
	repl.cpp
	quit/operation.cpp)
    
target_link_libraries (mu_repl
    gc
    boost_system
    boost_filesystem
    mu_core
    mu_io
    mu_script)