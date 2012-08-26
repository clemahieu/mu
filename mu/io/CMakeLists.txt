cmake_minimum_required (VERSION 2.8)
project (io)

add_library (mu_io SHARED
	context.cpp
	position.cpp
	source.cpp
    analyzer/name_map.cpp
	analyzer/resolver.cpp
	ast/cluster.cpp
	ast/expression.cpp
	ast/identifier.cpp
	ast/node.cpp
	ast/parameters.cpp
    ast/value.cpp
	ast/visitor.cpp
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
	tokens/divider.cpp
	tokens/identifier.cpp
	tokens/left_square.cpp
	tokens/right_square.cpp
	tokens/stream_end.cpp
	tokens/token.cpp
    tokens/value.cpp
	tokens/visitor.cpp)
    
target_link_libraries (mu_io
    gc
    mu_core)