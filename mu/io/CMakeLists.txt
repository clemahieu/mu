cmake_minimum_required (VERSION 2.8)
project (io)

include_directories (${CMAKE_SOURCE_DIR}/cryptopp)

add_library (mu_io STATIC
	builder.cpp
	source.cpp
	analyzer/analyzer.cpp
	analyzer/expression.cpp
	analyzer/resolver.cpp
	analyzer/routine.cpp
	analyzer/extensions/extension.cpp
	analyzer/extensions/extensions.cpp
	analyzer/extensions/global.cpp
	ast/builder.cpp
	ast/cluster.cpp
	ast/expression.cpp
	ast/identifier.cpp
	ast/node.cpp
	ast/parameters.cpp
	ast/visitor.cpp
	debugging/context.cpp
	debugging/position.cpp
	lexer/begin.cpp
	lexer/character_stream.cpp
	lexer/complex_identifier.cpp
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
	tokens/visitor.cpp)