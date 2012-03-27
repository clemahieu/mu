cmake_minimum_required (VERSION 2.8)
project (exec)

link_directories (${CMAKE_SOURCE_DIR}/boost/stage/lib)
link_directories (${CMAKE_SOURCE_DIR}/cryptopp/x64/Output/Debug)

add_executable (mu_exec
	main.cpp)

target_link_libraries (mu_exec
	mu_core
	mu_io
	mu_script)

if (NOT WIN32)
	target_link_libraries (mu_exec
		boost_filesystem
		boost_system)
endif ()

target_link_libraries (mu_exec
	cryptlib.lib)