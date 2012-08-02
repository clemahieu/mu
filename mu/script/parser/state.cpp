#include <mu/script/parser/state.h>

#include <mu/io/tokens/token.h>
#include <mu/core/errors/error_target.h>

void mu::script::parser::state::unexpected_token (mu::core::errors::error_target & errors_a, mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    mu::stringstream message;
    message << U"Unexpected token: ";
    message << token_a->token_name ();
    message << U" at: ";
    message << context_a.string ();
    errors_a (message.str ());
}