cmake_minimum_required (VERSION 2.8)
project (io)

add_library (mu_io SHARED
	character.hpp
	lexer.cpp
	lexer.hpp
	position.hpp
	region.hpp
	stream.hpp
	stream_istream.cpp
	stream_istream.hpp
	tokens.cpp
	tokens.hpp)
    
target_link_libraries (mu_io
	mu_core
	gc)