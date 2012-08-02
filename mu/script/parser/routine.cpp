#include <mu/script/parser/routine.h>

#include <mu/script/parser/parser.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/right_square.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/parameters.h>
#include <mu/io/tokens/value.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/left_square.h>
#include <mu/script/parser/body.h>
#include <mu/script/parser/parameters.h>

#include <assert.h>

#include <gc_cpp.h>

mu::script::parser::routine::routine (mu::script::parser::parser & parser_a):
state (mu::script::parser::routine_state::name),
parser (parser_a)
{
}

void mu::script::parser::routine::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    if (state == mu::script::parser::routine_state::end)
    {
        parser.state.pop ();
        parser (token_a, context_a);
    }
    else
    {
        context = context_a;
        (*token_a) (this);
    }
}

void mu::script::parser::routine::operator () (mu::io::tokens::divider * token)
{
    switch (state)
    {
        case mu::script::parser::routine_state::parameters:
            state = mu::script::parser::routine_state::body;
            named_parameters = false;
            break;
        case mu::script::parser::routine_state::name:
        case mu::script::parser::routine_state::body:
            unexpected_token (parser.errors, token, context);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::routine::operator () (mu::io::tokens::identifier * token)
{
    switch (state)
    {
        case mu::script::parser::routine_state::name:
            state = mu::script::parser::routine_state::parameters;
            name = token->string;
            break;
        case mu::script::parser::routine_state::parameters:
        case mu::script::parser::routine_state::body:
            unexpected_token (parser.errors, token, context);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::routine::operator () (mu::io::tokens::left_square * token)
{
    switch (state)
    {
        case mu::script::parser::routine_state::parameters:
            state = mu::script::parser::routine_state::body;
            named_parameters = true;
            parser.state.push (new (GC) mu::script::parser::parameters (*this));
            break;
        case mu::script::parser::routine_state::body:
            state = mu::script::parser::routine_state::end;
            parser.state.push (new (GC) mu::script::parser::body (*this));
            break;
        case mu::script::parser::routine_state::name:
            unexpected_token (parser.errors, token, context);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::routine::operator () (mu::io::tokens::right_square * token)
{
    unexpected_token (parser.errors, token, context);
}

void mu::script::parser::routine::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (parser.errors, token, context);
}

void mu::script::parser::routine::operator () (mu::io::tokens::parameters * token)
{
    unexpected_token (parser.errors, token, context);
}

void mu::script::parser::routine::operator () (mu::io::tokens::value * token)
{
    unexpected_token (parser.errors, token, context);
}