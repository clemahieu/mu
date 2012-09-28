cmake_minimum_required (VERSION 2.8)
project (io)

add_library (mu_io SHARED
    analyzer_begin.cpp
    analyzer_error.cpp
    analyzer_extensions.cpp
    analyzer_global.cpp
    analyzer_analyzer.cpp
	context.cpp
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
        scope_block.cpp
        scope_global.cpp
        scope_scope.cpp
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