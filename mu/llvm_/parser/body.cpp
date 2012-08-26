#include <mu/llvm_/parser/body.h>

#include <mu/io/tokens/implementor.h>
#include <mu/llvm_/parser/routine.h>
#include <mu/llvm_/parser/parser.h>
#include <mu/llvm_/parser/cluster.h>
#include <mu/llvm_/parser/expression.h>
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

void mu::llvm_::parser::body::operator () (mu::io::tokens::divider * token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::llvm_::parser::body::operator () (mu::io::tokens::identifier * token)
{
    routine.cluster.map.fill_reference (token->string, token->context, routine.routine_m->body->nodes);
}

void mu::llvm_::parser::body::operator () (mu::io::tokens::left_square * token)
{
    auto state_l (new (GC) mu::llvm_::parser::expression (routine));
    routine.routine_m->body->nodes.nodes.push_back (state_l->expression_m);
    routine.cluster.parser.state.push (state_l);
}

void mu::llvm_::parser::body::operator () (mu::io::tokens::right_square * token)
{
    routine.cluster.parser.state.pop ();
}

void mu::llvm_::parser::body::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::llvm_::parser::body::operator () (mu::io::tokens::value * token)
{
    routine.routine_m->body->nodes.nodes.push_back (token->node);
}