#include <mu/script/parser_body.h>

#include <mu/io/tokens_implementor.h>
#include <mu/script/parser_routine.h>
#include <mu/script/parser_parser.h>
#include <mu/script/parser_cluster.h>
#include <mu/script/ast_definite_expression.h>
#include <mu/script/parser_expression.h>
#include <mu/script/ast_reference.h>
#include <mu/core/node_list.h>

#include <gc_cpp.h>

mu::script::parser::body::body (mu::script::parser::routine & routine_a, mu::script::ast::definite_expression * expression_a):
routine (routine_a),
expression_m (expression_a)
{
}

void mu::script::parser::body::operator () (mu::io::tokens::token * token_a)
{
    (*token_a) (this);
}

void mu::script::parser::body::operator () (mu::io::tokens::divider * token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::script::parser::body::operator () (mu::io::tokens::identifier * token)
{
    routine.cluster.map.fill_reference (token->string, token->context, expression_m->nodes);
}

void mu::script::parser::body::operator () (mu::io::tokens::left_square * token)
{
    auto expression_l (new (GC) mu::script::ast::definite_expression);
    expression_m->nodes.nodes.push_back (expression_l);
    auto state_l (new (GC) mu::script::parser::expression (routine, expression_l));
    routine.cluster.parser.state.push (state_l);
}

void mu::script::parser::body::operator () (mu::io::tokens::right_square * token)
{
    routine.cluster.parser.state.pop ();
}

void mu::script::parser::body::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::script::parser::body::operator () (mu::io::tokens::value * token)
{
    expression_m->nodes.nodes.push_back (token->node);
}