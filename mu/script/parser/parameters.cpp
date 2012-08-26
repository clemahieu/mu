#include <mu/script/parser/parameters.h>

#include <mu/io/tokens_implementor.h>
#include <mu/script/parser/routine.h>
#include <mu/script/parser/parser.h>
#include <mu/script/runtime/selection.h>
#include <mu/script/parser/cluster.h>
#include <mu/script/ast_parameter.h>

#include <gc_cpp.h>

mu::script::parser::parameters::parameters (mu::script::parser::routine & routine_a):
routine (routine_a)
{
}

void mu::script::parser::parameters::operator () (mu::io::tokens::token * token_a)
{
    (*token_a) (this);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::divider * token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::identifier * token)
{
    routine.cluster.map.insert_local (routine.cluster.parser.errors, token->string, new (GC) mu::script::ast::parameter (routine.parameters), token->context);
    ++routine.parameters;
}

void mu::script::parser::parameters::operator () (mu::io::tokens::left_square * token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::right_square * token)
{
    routine.cluster.parser.state.pop ();
}

void mu::script::parser::parameters::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (routine.cluster.parser, token);
}
void mu::script::parser::parameters::operator () (mu::io::tokens::value * token)
{
    unexpected_token (routine.cluster.parser, token);
}