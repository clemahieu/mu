#include <mu/script/parser_keyword_if.h>

#include <mu/io/tokens_token.h>
#include <mu/io/tokens_implementor.h>
#include <mu/script/parser_routine.h>
#include <mu/script/parser_cluster.h>
#include <mu/script/parser_parser.h>
#include <mu/script/ast_if_expression.h>
#include <mu/script/ast_reference.h>
#include <mu/script/tokens_keyword_if.h>
#include <mu/script/ast_definite_expression.h>
#include <mu/script/parser_expression.h>

#include <gc_cpp.h>

#include <assert.h>

mu::script::parser::keyword_if::keyword_if (mu::script::parser::routine & routine_a, mu::script::ast::if_expression * expression_a) :
routine (routine_a),
state (mu::script::parser::keyword_if_state::initial),
expression (expression_a),
element (0)
{
}

void mu::script::parser::keyword_if::operator () (mu::io::tokens::token * token_a)
{
    (*token_a) (this);
}

void mu::script::parser::keyword_if::operator () (mu::io::tokens::divider * token)
{
    switch (state)
    {
        case mu::script::parser::keyword_if_state::predicate:
            state = mu::script::parser::keyword_if_state::true_branch;
            break;
        case mu::script::parser::keyword_if_state::true_branch:
            state = mu::script::parser::keyword_if_state::false_branch;
            break;
        case mu::script::parser::keyword_if_state::false_branch:
            state = mu::script::parser::keyword_if_state::name;
            break;
        case mu::script::parser::keyword_if_state::name:
            state = mu::script::parser::keyword_if_state::have_name;
            break;
        case mu::script::parser::keyword_if_state::have_name:
            state = mu::script::parser::keyword_if_state::elements;
            break;
        case mu::script::parser::keyword_if_state::initial:
        case mu::script::parser::keyword_if_state::elements:
            unexpected_token(routine.cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::keyword_if::operator () (mu::io::tokens::identifier * token)
{
    switch (state)
    {
        case mu::script::parser::keyword_if_state::predicate:
            routine.cluster.map.fill_reference (token->string, token->context, expression->predicate);
            break;
        case mu::script::parser::keyword_if_state::true_branch:
            routine.cluster.map.fill_reference (token->string, token->context, expression->true_branch);
            break;
        case mu::script::parser::keyword_if_state::false_branch:
            routine.cluster.map.fill_reference (token->string, token->context, expression->false_branch);
            break;
        case mu::script::parser::keyword_if_state::name:
            state = mu::script::parser::keyword_if_state::have_name;
            routine.cluster.map.insert_routine_scope (routine.cluster.parser.errors, token->string, expression, token->context);
            break;
        case mu::script::parser::keyword_if_state::have_name:
            unexpected_token (routine.cluster.parser, token);
            break;
        case mu::script::parser::keyword_if_state::elements:
            routine.cluster.map.insert_routine_scope (routine.cluster.parser.errors, token->string, new (GC) mu::script::ast::reference (expression, element), token->context);
            ++element;
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::keyword_if::operator () (mu::io::tokens::left_square * token)
{
    switch (state)
    {
        case mu::script::parser::keyword_if_state::predicate:
            process_left_square (expression->predicate);
            break;
        case mu::script::parser::keyword_if_state::true_branch:
            process_left_square (expression->true_branch);
            break;
        case mu::script::parser::keyword_if_state::false_branch:
            process_left_square (expression->false_branch);
            break;
        case mu::script::parser::keyword_if_state::name:
        case mu::script::parser::keyword_if_state::have_name:
        case mu::script::parser::keyword_if_state::elements:
            unexpected_token(routine.cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::keyword_if::operator () (mu::io::tokens::right_square * token)
{
    routine.cluster.parser.state.pop ();
}

void mu::script::parser::keyword_if::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::script::parser::keyword_if::operator () (mu::io::tokens::value * token)
{
    switch (state)
    {
        case mu::script::parser::keyword_if_state::predicate:
            process_value (token, expression->predicate);
            break;
        case mu::script::parser::keyword_if_state::true_branch:
            process_value (token, expression->true_branch);
            break;
        case mu::script::parser::keyword_if_state::false_branch:
            process_value (token, expression->false_branch);
            break;
        case mu::script::parser::keyword_if_state::have_name:
        case mu::script::parser::keyword_if_state::name:
        case mu::script::parser::keyword_if_state::elements:
            unexpected_token (routine.cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::keyword_if::process_left_square (mu::core::node_list & nodes_a)
{
    auto expression_l (new (GC) mu::script::ast::definite_expression);
    nodes_a.nodes.push_back (expression_l);
    auto state_l (new (GC) mu::script::parser::expression (routine, expression_l));
    routine.cluster.parser.state.push (state_l);
}

void mu::script::parser::keyword_if::process_value (mu::io::tokens::value * token, mu::core::node_list & nodes_a)
{
    auto if_l (dynamic_cast <mu::script::tokens::keyword_if *> (token->node));
    if (if_l != nullptr)
    {
        auto expression_l (new (GC) mu::script::ast::if_expression);
        nodes_a.nodes.push_back (expression_l);
        auto state_l (new (GC) mu::script::parser::keyword_if (routine, expression_l));
        routine.cluster.parser.state.push (state_l);
    }
    else
    {
        expression->predicate.nodes.push_back (token->node);
    }
}