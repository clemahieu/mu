cmake_minimum_required (VERSION 2.8)

add_llvm_library (mu_io
	lexer.cpp
	lexer.hpp
    stream.hpp
	stream_istream.cpp
	stream_istream.hpp
    stream_token.cpp
    stream_token.hpp
	tokens.cpp
	tokens.hpp)