cmake_minimum_required (VERSION 2.8)
project (mu)

if (UNIX OR MINGW)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()

file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/temp)
set (CMAKE_VERBOSE_MAKEFILE "ON")
add_definitions (-D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS)

set (llvm_include_directories
	${CMAKE_SOURCE_DIR}/llvm/include)
set (boost_include_directories
	${CMAKE_SOURCE_DIR}/boost)
set (gtest_include_directories
	${CMAKE_SOURCE_DIR}/googletest/include)
set (gc_include_directories
	${CMAKE_SOURCE_DIR}/gc/include)

set (boost_lib_directories
	${CMAKE_SOURCE_DIR}/boost/stage/lib)
if (WIN32)
	set (llvm_lib_directories
		${CMAKE_SOURCE_DIR}/llvm/lib)
else (WIN32)
	set (llvm_lib_directories
		"${CMAKE_SOURCE_DIR}/llvm/Debug+Asserts/lib")
endif (WIN32)
set (gc_lib_directories
	${CMAKE_SOURCE_DIR}/gc/.libs)
set (gtest_lib_directories
	${CMAKE_SOURCE_DIR}/googletest)

include_directories (
	${CMAKE_SOURCE_DIR}
	${boost_include_directories}
	${gc_include_directories})

link_directories (
	${boost_lib_directories}
	${gc_lib_directories})

add_subdirectory (mu/binary_test)
add_subdirectory (mu/core)
add_subdirectory (mu/exec)
add_subdirectory (mu/io)
add_subdirectory (mu/llvm_)
add_subdirectory (mu/llvm_binary)
add_subdirectory (mu/repl)
add_subdirectory (mu/repl_entry)
add_subdirectory (mu/script)
add_subdirectory (mu/script_binary)
add_subdirectory (mu/script_core_binary)
add_subdirectory (mu/test_entry)
file (COPY ${CMAKE_SOURCE_DIR}/examples DESTINATION ${CMAKE_BINARY_DIR})
file (COPY ${CMAKE_SOURCE_DIR}/source_test.mu DESTINATION ${CMAKE_BINARY_DIR})
file (COPY ${CMAKE_SOURCE_DIR}/mu/source DESTINATION ${CMAKE_BINARY_DIR}/mu)