#include <mu/script/parser/parameters.h>

#include <mu/io/tokens/token.h>
#include <mu/script/parser/routine.h>
#include <mu/script/parser/parser.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/left_square.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/parameters.h>
#include <mu/io/tokens/value.h>
#include <mu/io/tokens/identifier.h>

mu::script::parser::parameters::parameters (mu::script::parser::routine & routine_a):
routine (routine_a)
{
}

void mu::script::parser::parameters::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    context = context_a;
    (*token_a) (this);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::divider * token)
{
    unexpected_token (routine.parser.errors, token, context);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::identifier * token)
{
    routine.parameters.push_back (token->string);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::left_square * token)
{
    unexpected_token (routine.parser.errors, token, context);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::right_square * token)
{
    routine.parser.state.pop ();
}

void mu::script::parser::parameters::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (routine.parser.errors, token, context);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::parameters * token)
{
    unexpected_token (routine.parser.errors, token, context);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::value * token)
{
    unexpected_token (routine.parser.errors, token, context);
}