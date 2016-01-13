cmake_minimum_required (VERSION 2.8)

add_llvm_library (mu_core
	error.cpp
	error.hpp
	error_string.cpp
	error_string.hpp
	lexer.cpp
	lexer.hpp
	region.cpp
	region.hpp
	siphash24.c
	stream_istream.cpp
	stream_istream.hpp
	stream_token.cpp
	stream_token.hpp
	string_hash.cpp
	string_hash.hpp
	tokens.cpp
	tokens.hpp
	types.cpp
	types.hpp)
