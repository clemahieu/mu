#include <mu/llvm_/parser/expression.h>

#include <mu/io/tokens/divider.h>
#include <mu/llvm_/parser/routine.h>
#include <mu/llvm_/parser/cluster.h>
#include <mu/io/tokens/identifier.h>
#include <mu/llvm_/parser/parser.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/parameters.h>
#include <mu/io/tokens/value.h>
#include <mu/io/tokens/right_square.h>
#include <mu/llvm_/ast_expression.h>
#include <mu/llvm_/ast_reference.h>

#include <gc_cpp.h>

#include <assert.h>

mu::llvm_::parser::expression::expression (mu::llvm_::parser::routine & routine_a):
state (mu::llvm_::parser::expression_state::values),
routine (routine_a),
element (~0),
expression_m (new (GC) mu::llvm_::ast::expression)
{
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    context = context_a;
    (*token_a) (this);
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::divider * token)
{
    switch (state)
    {
        case mu::llvm_::parser::expression_state::values:
            state = mu::llvm_::parser::expression_state::name;
            break;
        case mu::llvm_::parser::expression_state::name:
        case mu::llvm_::parser::expression_state::have_name:
            state = mu::llvm_::parser::expression_state::elements;
            break;
        case mu::llvm_::parser::expression_state::elements:
            unexpected_token (routine.cluster.parser, token, context);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::identifier * token)
{
    switch (state)
    {
        case mu::llvm_::parser::expression_state::values:
            routine.cluster.map.fill_reference (token->string, context, expression_m->nodes);
            break;
        case mu::llvm_::parser::expression_state::name:
            routine.cluster.map.insert_local (routine.cluster.parser.errors, token->string, expression_m, context);
            state = mu::llvm_::parser::expression_state::have_name;
            break;
        case mu::llvm_::parser::expression_state::have_name:
            unexpected_token (routine.cluster.parser, token, context);
            break;
        case mu::llvm_::parser::expression_state::elements:
            routine.cluster.map.insert_local(routine.cluster.parser.errors, token->string, new (GC) mu::llvm_::ast::reference (expression_m, ++element), context);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::left_square * token)
{
    auto state_l (new (GC) mu::llvm_::parser::expression (routine));
    expression_m->nodes.nodes.push_back (state_l->expression_m);
    routine.cluster.parser.state.push (state_l);
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::right_square * token)
{
    switch (state)
    {
        case mu::llvm_::parser::expression_state::name:
            unexpected_token (routine.cluster.parser, token, context);
            break;
        case mu::llvm_::parser::expression_state::values:
        case mu::llvm_::parser::expression_state::have_name:
        case mu::llvm_::parser::expression_state::elements:
            break;
        default:
            assert (false);
            break;
    }
    routine.cluster.parser.state.pop ();
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::parameters * token)
{
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::value * token)
{
    switch (state)
    {
        case mu::llvm_::parser::expression_state::values:
            expression_m->nodes.nodes.push_back (token->node);
            break;
        case mu::llvm_::parser::expression_state::name:
        case mu::llvm_::parser::expression_state::have_name:
        case mu::llvm_::parser::expression_state::elements:
            unexpected_token (routine.cluster.parser, token, context);
            break;
        default:
            assert (false);
            break;
    }
}