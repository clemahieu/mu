cmake_minimum_required (VERSION 2.8)
project (script_binary)

link_directories (${CMAKE_SOURCE_DIR}/boost/stage/lib)
link_directories (${CMAKE_SOURCE_DIR}/cryptopp/x64/Output/Debug)

add_library (mu_script_binary MODULE
	entry.cpp)
	
target_link_libraries (mu_script_binary
	mu_core
	mu_io
	mu_script)

if (NOT WIN32)
	target_link_libraries (mu_script_binary
		boost_filesystem
		boost_system)
endif ()

target_link_libraries (mu_script_binary
	cryptlib.lib)