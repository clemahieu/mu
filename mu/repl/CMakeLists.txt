cmake_minimum_required (VERSION 2.8)
project (repl)

include_directories (${CMAKE_SOURCE_DIR}/gc/include)

link_directories (${CMAKE_SOURCE_DIR}/gc/.libs)
link_directories (${CMAKE_SOURCE_DIR}/boost/stage/lib)

add_library (mu_repl SHARED
	cli_stream.cpp
	data_stream.cpp
	repl.cpp
	quit/operation.cpp)
    
target_link_libraries (mu_repl
    gc
    mu_core
    mu_script)