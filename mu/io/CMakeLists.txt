cmake_minimum_required (VERSION 2.8)
project (io)

add_library (mu_io SHARED
    analyzer_name_map.cpp
	analyzer_resolver.cpp
	ast_cluster.cpp
	ast_expression.cpp
	ast_identifier.cpp
	ast_node.cpp
	ast_parameters.cpp
    ast_value.cpp
	ast_visitor.cpp
	context.cpp
    keywording_begin.cpp
    keywording_error.cpp
    keywording_extensions.cpp
    keywording_global.cpp
    keywording_keywording.cpp
	lexer_begin.cpp
	lexer_character_stream.cpp
	lexer_complex_identifier.cpp
    lexer_context.cpp
	lexer_control.cpp
	lexer_error.cpp
	lexer_error_target.cpp
	lexer_hex_code.cpp
	lexer_identifier.cpp
	lexer_istream_input.cpp
	lexer_lexer.cpp
	lexer_multiline_comment.cpp
	lexer_singleline_comment.cpp
	lexer_state.cpp
    lexer_stream_input.cpp
	lexer_token_vector.cpp
	lexer_wistream_input.cpp
	position.cpp
	source.cpp
	tokens_divider.cpp
	tokens_identifier.cpp
	tokens_left_square.cpp
	tokens_right_square.cpp
	tokens_stream_end.cpp
	tokens_token.cpp
    tokens_value.cpp
	tokens_visitor.cpp)
    
target_link_libraries (mu_io
    gc
    mu_core)