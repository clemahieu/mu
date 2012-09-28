#include <mu/script/parser_body.h>

#include <mu/io/tokens_implementor.h>
#include <mu/script/parser_routine.h>
#include <mu/script/parser_parser.h>
#include <mu/script/parser_cluster.h>
#include <mu/script/ast_definite_expression.h>
#include <mu/script/parser_expression.h>
#include <mu/script/ast_reference.h>
#include <mu/core/node_list.h>
#include <mu/script/tokens_keyword_if.h>
#include <mu/script/ast_if_expression.h>
#include <mu/script/parser_keyword_if.h>

#include <gc_cpp.h>

mu::script::parser::body::body (mu::script::parser::routine & routine_a, mu::script::ast::definite_expression * expression_a):
routine (routine_a),
expression_m (expression_a)
{
}

void mu::script::parser::body::operator () (mu::io::tokens::token const & token_a)
{
    token_a (this);
}

void mu::script::parser::body::operator () (mu::io::tokens::divider const & token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::script::parser::body::operator () (mu::io::tokens::identifier const & token)
{
    routine.scope.refer (token.string, token.context, expression_m->nodes);
}

void mu::script::parser::body::operator () (mu::io::tokens::left_square const & token)
{
    auto expression_l (new (GC) mu::script::ast::definite_expression);
    expression_m->nodes.nodes.push_back (expression_l);
    auto state_l (new (GC) mu::script::parser::expression (routine, expression_l));
    routine.cluster.parser.state.push (state_l);
}

void mu::script::parser::body::operator () (mu::io::tokens::right_square const & token)
{
    routine.cluster.parser.state.pop ();
}

void mu::script::parser::body::operator () (mu::io::tokens::stream_end const & token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::script::parser::body::operator () (mu::io::tokens::value const & token)
{
    auto if_l (dynamic_cast <mu::script::tokens::keyword_if *> (token.node));
    if (if_l != nullptr)
    {
        auto expression_l (new (GC) mu::script::ast::if_expression);
        expression_m->nodes.nodes.push_back (expression_l);
        auto state_l (new (GC) mu::script::parser::keyword_if (routine, expression_l));
        routine.cluster.parser.state.push (state_l);
    }
    else
    {
        expression_m->nodes.nodes.push_back (token.node);
    }
}