cmake_minimum_required (VERSION 2.8)
project (io)

include_directories (${CMAKE_SOURCE_DIR}/gc/include)

link_directories (${CMAKE_SOURCE_DIR}/gc/.libs)

add_library (mu_io SHARED
	builder.cpp
	source.cpp
	analyzer/analyzer.cpp
	analyzer/expression.cpp
    analyzer/name_map.cpp
	analyzer/resolver.cpp
	analyzer/routine.cpp
	ast/builder.cpp
	ast/cluster.cpp
	ast/expression.cpp
	ast/identifier.cpp
	ast/node.cpp
	ast/parameters.cpp
    ast/value.cpp
	ast/visitor.cpp
	debugging/context.cpp
	debugging/position.cpp
    keywording/begin.cpp
    keywording/error.cpp
    keywording/extensions.cpp
    keywording/global.cpp
    keywording/keywording.cpp
	lexer/begin.cpp
	lexer/character_stream.cpp
	lexer/complex_identifier.cpp
    lexer/context.cpp
	lexer/control.cpp
	lexer/error.cpp
	lexer/error_target.cpp
	lexer/hex_code.cpp
	lexer/identifier.cpp
	lexer/istream_input.cpp
	lexer/lexer.cpp
	lexer/multiline_comment.cpp
	lexer/singleline_comment.cpp
	lexer/state.cpp
    lexer/stream_input.cpp
	lexer/token_vector.cpp
	lexer/wistream_input.cpp
	parser/begin.cpp
	parser/error.cpp
	parser/error_target.cpp
	parser/finished.cpp
	parser/full.cpp
	parser/parser.cpp
	parser/single.cpp
	parser/values.cpp
	tokens/divider.cpp
	tokens/identifier.cpp
	tokens/left_square.cpp
	tokens/parameters.cpp
	tokens/right_square.cpp
	tokens/stream_end.cpp
	tokens/token.cpp
    tokens/value.cpp
	tokens/visitor.cpp)
    
target_link_libraries (mu_io
    gc
    mu_core)