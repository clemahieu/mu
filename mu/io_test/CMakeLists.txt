cmake_minimum_required (VERSION 2.8)
project (io_test)

add_library (mu_io_test STATIC
	analyzer.cpp
	analyzer_result.cpp
	begin.cpp
	builder.cpp
	complex_identifier.cpp
	control.cpp
	extension.cpp
	extension1.cpp
	extension2.cpp
	extension3.cpp
	extension4.cpp
	full.cpp
	hex_code.cpp
	istream_input_test.cpp
	lexer.cpp
	lexer_result.cpp
	multiline_comment.cpp
	parser.cpp
	parser_result.cpp
	routine.cpp
	single.cpp
	source.cpp
	source_result.cpp
	tests.cpp
	values.cpp
	wistream_input_test.cpp)