cmake_minimum_required (VERSION 2.8)
project (io)

add_library (mu_io SHARED
	lexer.cpp
	lexer.hpp
    stream.hpp
	stream_istream.cpp
	stream_istream.hpp
	stream_muistream.cpp
	stream_muistream.hpp
    stream_token.cpp
    stream_token.hpp
	tokens.cpp
	tokens.hpp)
    
target_link_libraries (mu_io
	mu_core
	gc)