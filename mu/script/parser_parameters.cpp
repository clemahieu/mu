#include <mu/script/parser_parameters.h>

#include <mu/io/tokens_implementor.h>
#include <mu/script/parser_routine.h>
#include <mu/script/parser_parser.h>
#include <mu/script/runtime_selection.h>
#include <mu/script/parser_cluster.h>
#include <mu/script/ast_parameter.h>

#include <gc_cpp.h>

mu::script::parser::parameters::parameters (mu::script::parser::routine & routine_a):
routine (routine_a)
{
}

void mu::script::parser::parameters::operator () (mu::io::tokens::token const & token_a)
{
    token_a (this);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::divider const & token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::identifier const & token)
{
    routine.scope.declare (routine.cluster.parser.errors, token.string, new (GC) mu::script::ast::parameter (routine.parameters), token.context);
    ++routine.parameters;
}

void mu::script::parser::parameters::operator () (mu::io::tokens::left_square const & token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::script::parser::parameters::operator () (mu::io::tokens::right_square const & token)
{
    routine.cluster.parser.state.pop ();
}

void mu::script::parser::parameters::operator () (mu::io::tokens::stream_end const & token)
{
    unexpected_token (routine.cluster.parser, token);
}
void mu::script::parser::parameters::operator () (mu::io::tokens::value const & token)
{
    unexpected_token (routine.cluster.parser, token);
}