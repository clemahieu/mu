#include <mu/script/parser_expression.h>

#include <mu/io/tokens_implementor.h>
#include <mu/script/ast_definite_expression.h>
#include <mu/script/parser_routine.h>
#include <mu/script/parser_cluster.h>
#include <mu/script/parser_parser.h>
#include <mu/script/runtime_selection.h>
#include <mu/script/runtime_fixed.h>
#include <mu/script/ast_reference.h>
#include <mu/core/node_list.h>
#include <mu/script/tokens_keyword_if.h>
#include <mu/script/parser_keyword_if.h>
#include <mu/script/ast_if_expression.h>

#include <gc_cpp.h>

#include <assert.h>

mu::script::parser::expression::expression (mu::script::parser::routine & routine_a, mu::script::ast::definite_expression * expression_a):
expression_m (expression_a),
state (mu::script::parser::expression_state::values),
routine (routine_a),
element (0)
{
}

void mu::script::parser::expression::operator () (mu::io::tokens::token * token_a)
{
    (*token_a) (this);
}

void mu::script::parser::expression::operator () (mu::io::tokens::divider * token)
{
    switch (state)
    {
        case mu::script::parser::expression_state::values:
            state = mu::script::parser::expression_state::name;
            break;
        case mu::script::parser::expression_state::name:
        case mu::script::parser::expression_state::have_name:
            state = mu::script::parser::expression_state::elements;
            break;
        case mu::script::parser::expression_state::elements:
            unexpected_token (routine.cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::expression::operator () (mu::io::tokens::identifier * token)
{
    switch (state)
    {
        case mu::script::parser::expression_state::values:
        {
            routine.cluster.map.fill_reference (token->string, token->context, expression_m->nodes);
            break;
        }
        case mu::script::parser::expression_state::name:
            routine.cluster.map.insert_routine_scope (routine.cluster.parser.errors, token->string, expression_m, token->context);
            state = mu::script::parser::expression_state::have_name;
            break;
        case mu::script::parser::expression_state::have_name:
            unexpected_token (routine.cluster.parser, token);
            break;
        case mu::script::parser::expression_state::elements:
            routine.cluster.map.insert_routine_scope (routine.cluster.parser.errors, token->string, new (GC) mu::script::ast::reference (expression_m, element), token->context);
            ++element;
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::expression::operator () (mu::io::tokens::left_square * token)
{
    auto expression_l (new (GC) mu::script::ast::definite_expression);
    expression_m->nodes.nodes.push_back (expression_l);
    auto state_l (new (GC) mu::script::parser::expression (routine, expression_l));
    routine.cluster.parser.state.push (state_l);
}

void mu::script::parser::expression::operator () (mu::io::tokens::right_square * token)
{
    switch (state)
    {
        case mu::script::parser::expression_state::name:
            unexpected_token (routine.cluster.parser, token);
            break;
        case mu::script::parser::expression_state::values:
        case mu::script::parser::expression_state::have_name:
        case mu::script::parser::expression_state::elements:
            break;
        default:
            assert (false);
            break;
    }
    routine.cluster.parser.state.pop ();
}

void mu::script::parser::expression::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (routine.cluster.parser, token);
}

void mu::script::parser::expression::operator () (mu::io::tokens::value * token)
{
    switch (state)
    {
        case mu::script::parser::expression_state::values:
        {
            auto if_l (dynamic_cast <mu::script::tokens::keyword_if *> (token->node));
            if (if_l != nullptr)
            {
                auto expression_l (new (GC) mu::script::ast::if_expression);
                expression_m->nodes.nodes.push_back (expression_l);
                auto state_l (new (GC) mu::script::parser::keyword_if (routine, expression_l));
                routine.cluster.parser.state.push (state_l);
            }
            else
            {
                expression_m->nodes.nodes.push_back (token->node);        
            }
        }
            break;
        case mu::script::parser::expression_state::name:
        case mu::script::parser::expression_state::have_name:
        case mu::script::parser::expression_state::elements:
            unexpected_token (routine.cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}