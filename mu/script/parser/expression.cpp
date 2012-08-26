#include <mu/script/parser/expression.h>

#include <mu/io/tokens/implementor.h>
#include <mu/script/ast_expression.h>
#include <mu/script/parser/routine.h>
#include <mu/script/parser/cluster.h>
#include <mu/script/parser/parser.h>
#include <mu/script/runtime/selection.h>
#include <mu/script/runtime/fixed.h>
#include <mu/script/ast_reference.h>
#include <mu/core/node_list.h>

#include <gc_cpp.h>

#include <assert.h>

mu::script::parser::expression::expression (mu::script::parser::routine & routine_a, mu::script::ast::expression * expression_a):
expression_m (expression_a),
state (mu::script::parser::expression_state::values),
routine (routine_a),
element (0)
{
}

void mu::script::parser::expression::operator () (mu::io::tokens::token * token_a, mu::io::context context_a)
{
    context = context_a;
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
            unexpected_token (routine.cluster.parser, token, context);
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
            routine.cluster.map.fill_reference (token->string, context, expression_m->nodes);
            break;
        }
        case mu::script::parser::expression_state::name:
            routine.cluster.map.insert_local (routine.cluster.parser.errors, token->string, expression_m, context);
            state = mu::script::parser::expression_state::have_name;
            break;
        case mu::script::parser::expression_state::have_name:
            unexpected_token (routine.cluster.parser, token, context);
            break;
        case mu::script::parser::expression_state::elements:
            routine.cluster.map.insert_local (routine.cluster.parser.errors, token->string, new (GC) mu::script::ast::reference (expression_m, element), context);
            ++element;
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::expression::operator () (mu::io::tokens::left_square * token)
{
    auto expression_l (new (GC) mu::script::ast::expression);
    expression_m->nodes.nodes.push_back (expression_l);
    auto state_l (new (GC) mu::script::parser::expression (routine, expression_l));
    routine.cluster.parser.state.push (state_l);
}

void mu::script::parser::expression::operator () (mu::io::tokens::right_square * token)
{
    switch (state)
    {
        case mu::script::parser::expression_state::values:
            break;
        case mu::script::parser::expression_state::name:
            unexpected_token (routine.cluster.parser, token, context);
            break;
        case mu::script::parser::expression_state::have_name:
        case mu::script::parser::expression_state::elements:
                // When named, function does not nest
            break;
        default:
            assert (false);
            break;
    }
    routine.cluster.parser.state.pop ();
}

void mu::script::parser::expression::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::script::parser::expression::operator () (mu::io::tokens::value * token)
{
    switch (state)
    {
        case mu::script::parser::expression_state::values:
            expression_m->nodes.nodes.push_back (new (GC) mu::script::runtime::fixed (token->node));
            break;
        case mu::script::parser::expression_state::name:
        case mu::script::parser::expression_state::have_name:
        case mu::script::parser::expression_state::elements:
            unexpected_token (routine.cluster.parser, token, context);
            break;
        default:
            assert (false);
            break;
    }
}