#include <mu/llvm_/parser_body.h>

#include <mu/io/tokens_implementor.h>
#include <mu/llvm_/parser_routine.h>
#include <mu/llvm_/parser_parser.h>
#include <mu/llvm_/parser_cluster.h>
#include <mu/llvm_/parser_expression.h>
#include <mu/llvm_/ast_expression.h>
#include <mu/llvm_/ast_routine.h>

#include <gc_cpp.h>

mu::llvm_::parser::body::body (mu::llvm_::parser::routine & routine_a):
routine (routine_a)
{
}

void mu::llvm_::parser::body::operator () (mu::io::tokens::token * token_a)
{
    (*token_a) (this);
}

void mu::llvm_::parser::body::operator () (mu::io::tokens::divider const & token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::llvm_::parser::body::operator () (mu::io::tokens::identifier const & token)
{
    routine.scope.refer (token.string, token.context, routine.routine_m->body->nodes);
}

void mu::llvm_::parser::body::operator () (mu::io::tokens::left_square const & token)
{
    auto state_l (new (GC) mu::llvm_::parser::expression (routine));
    routine.routine_m->body->nodes.nodes.push_back (state_l->expression_m);
    routine.cluster.parser.state.push (state_l);
}

void mu::llvm_::parser::body::operator () (mu::io::tokens::right_square const & token)
{
    routine.cluster.parser.state.pop ();
}

void mu::llvm_::parser::body::operator () (mu::io::tokens::stream_end const & token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::llvm_::parser::body::operator () (mu::io::tokens::value const & token)
{
    routine.routine_m->body->nodes.nodes.push_back (token.node);
}