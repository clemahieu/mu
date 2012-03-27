cmake_minimum_required (VERSION 2.8)
project (repl_entry)

link_directories (${CMAKE_SOURCE_DIR}/boost/stage/lib)
link_directories (${CMAKE_SOURCE_DIR}/cryptopp/x64/Output/Debug)

add_executable (mu_repl_entry
	main.cpp)

target_link_libraries (mu_repl_entry
	mu_core
	mu_io
	mu_repl
	mu_script)

if (NOT WIN32)
	target_link_libraries (mu_repl_entry
		boost_filesystem
		boost_system)
endif ()

target_link_libraries (mu_repl_entry
	cryptlib.lib)