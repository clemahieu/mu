#include <mu/llvmc/partial_ast.hpp>

#include <mu/llvmc/parser.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/io/tokens.hpp>
#include <mu/core/error_string.hpp>

#include <gc_cpp.h>

mu::llvmc::partial_ast::partial_ast (mu::io::stream_token & tokens_a, mu::llvmc::parser & parser_a):
tokens (tokens_a),
parser (parser_a)
{
}