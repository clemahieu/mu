cmake_minimum_required (VERSION 2.8)
project (exec)

add_executable (mu_exec
	main.cpp)

if (WIN32)
	target_link_libraries (mu_exec
		gc
		boost_system-mgw47-mt-d-1_51
		boost_filesystem-mgw47-mt-d-1_51
		mu_core
		mu_io
		mu_script)
else (WIN32)	
	target_link_libraries (mu_exec
		gc
		boost_system
		boost_filesystem
		mu_core
		mu_io
		mu_script)
endif (WIN32)
