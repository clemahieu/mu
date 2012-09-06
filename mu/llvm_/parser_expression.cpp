#include <mu/llvm_/parser_expression.h>

#include <mu/io/tokens_implementor.h>
#include <mu/llvm_/parser_routine.h>
#include <mu/llvm_/parser_cluster.h>
#include <mu/llvm_/parser_parser.h>
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

void mu::llvm_::parser::expression::operator () (mu::io::tokens::token * token_a)
{
    (*token_a) (this);
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::divider const & token)
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
            unexpected_token (routine.cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::identifier const & token)
{
    switch (state)
    {
        case mu::llvm_::parser::expression_state::values:
            routine.cluster.map.fill_reference (token.string, token.context, expression_m->nodes);
            break;
        case mu::llvm_::parser::expression_state::name:
            routine.cluster.map.insert_routine_scope (routine.cluster.parser.errors, token.string, expression_m, token.context);
            state = mu::llvm_::parser::expression_state::have_name;
            break;
        case mu::llvm_::parser::expression_state::have_name:
            unexpected_token (routine.cluster.parser, token);
            break;
        case mu::llvm_::parser::expression_state::elements:
            routine.cluster.map.insert_routine_scope(routine.cluster.parser.errors, token.string, new (GC) mu::llvm_::ast::reference (expression_m, ++element), token.context);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::left_square const & token)
{
    auto state_l (new (GC) mu::llvm_::parser::expression (routine));
    expression_m->nodes.nodes.push_back (state_l->expression_m);
    routine.cluster.parser.state.push (state_l);
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::right_square const & token)
{
    switch (state)
    {
        case mu::llvm_::parser::expression_state::name:
            unexpected_token (routine.cluster.parser, token);
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

void mu::llvm_::parser::expression::operator () (mu::io::tokens::stream_end const & token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::value const & token)
{
    switch (state)
    {
        case mu::llvm_::parser::expression_state::values:
            expression_m->nodes.nodes.push_back (token.node);
            break;
        case mu::llvm_::parser::expression_state::name:
        case mu::llvm_::parser::expression_state::have_name:
        case mu::llvm_::parser::expression_state::elements:
            unexpected_token (routine.cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}