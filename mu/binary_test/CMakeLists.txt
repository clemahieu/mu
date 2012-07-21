cmake_minimum_required (VERSION 2.8)
project (binary_test)

include_directories (${CMAKE_SOURCE_DIR}/gc/include)

link_directories (${CMAKE_SOURCE_DIR}/gc/.libs)

add_library (mu_binary_test MODULE
	entry.cpp)
	
target_link_libraries (mu_binary_test
	mu_core
	mu_io
	mu_script)
    
if (NOT WIN32)
    set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -E")
endif (NOT WIN32)

target_link_libraries (mu_binary_test
    gc)