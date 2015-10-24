cmake_minimum_required (VERSION 2.8)
project (mu)

if (UNIX OR MINGW)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
endif ()

file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/temp)
set (CMAKE_VERBOSE_MAKEFILE "ON")
add_definitions (-D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -DGTEST_USE_OWN_TR1_TUPLE=0 -DGTEST_HAS_TR1_TUPLE=0 -D__STDC_FORMAT_MACROS)

find_package (Boost REQUIRED COMPONENTS filesystem program_options system)
include_directories (${Boost_INCLUDE_DIR})

find_package (LLVM REQUIRED)
MESSAGE (STATUS ${LLVM_CXXFLAGS})
MESSAGE (STATUS ${LLVM_LDFLAGS})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CXXFLAGS}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LLVM_LDFLAGS}")

find_package (GTest REQUIRED)
include_directories (${GTEST_INCLUDE_DIR})

include_directories (${CMAKE_SOURCE_DIR})

link_directories (${LLVM_LIBRARY_DIRS})

add_subdirectory (mu/core)
add_subdirectory (mu/io)
add_subdirectory (mu/llvmc)
add_subdirectory (mu/test)
add_subdirectory (mu/muc)
file (COPY ${CMAKE_SOURCE_DIR}/examples DESTINATION ${CMAKE_BINARY_DIR})
