cmake_minimum_required (VERSION 2.8)
project (io)

add_library (mu_io SHARED
	stream.hpp
	stream_istream.cpp
	stream_istream.hpp
	lexer_lexer.cpp
	lexer_lexer.hpp)
    
target_link_libraries (mu_io
    gc)