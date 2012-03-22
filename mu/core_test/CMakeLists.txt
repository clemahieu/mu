cmake_minimum_required (VERSION 2.8)
project (core_test)

add_library (mu_core_test STATIC
	apply.cpp
	directory_iterator_test.cpp
	filesystem_test.cpp
	list.cpp
	segment.cpp
	test_visitor.cpp
	tests.cpp
	visitor.cpp)

