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
#include <mu/script/runtime/selection.h>
#include <mu/script/parser/cluster.h>

#include <gc_cpp.h>

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
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::identifier * token)
{
    routine.cluster.map.insert_local (routine.cluster.parser.errors, token->string, new (GC) mu::script::runtime::selection (routine.parameters_m, routine.parameters), context);
    ++routine.parameters;
}

void mu::script::parser::parameters::operator () (mu::io::tokens::left_square * token)
{
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::right_square * token)
{
    routine.cluster.parser.state.pop ();
}

void mu::script::parser::parameters::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::parameters * token)
{
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::value * token)
{
    unexpected_token (routine.cluster.parser, token, context);
}