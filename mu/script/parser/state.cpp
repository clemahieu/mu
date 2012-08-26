#include <mu/script/parser/state.h>

#include <mu/io/tokens/token.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/parser/error.h>
#include <mu/script/parser/parser.h>

#include <gc_cpp.h>

void mu::script::parser::state::unexpected_token (mu::script::parser::parser & parser_a, mu::io::tokens::token * token_a, mu::io::context context_a)
{
    mu::stringstream message;
    message << U"Unexpected token: ";
    message << token_a->token_name ();
    message << U" at: ";
    message << context_a.string ();
    parser_a.errors (message.str ());
    parser_a.state.push (new (GC) mu::script::parser::error);
}