#include <mu/script/parser/expression.h>

#include <mu/script/runtime/expression.h>
#include <mu/io/tokens/divider.h>
#include <mu/script/parser/routine.h>
#include <mu/script/parser/cluster.h>
#include <mu/io/tokens/identifier.h>
#include <mu/script/parser/parser.h>
#include <mu/script/runtime/selection.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/parameters.h>
#include <mu/io/tokens/value.h>
#include <mu/script/runtime/fixed.h>

#include <gc_cpp.h>

#include <assert.h>

mu::script::parser::expression::expression (mu::script::parser::routine & routine_a):
expression_m (new (GC) mu::script::runtime::expression),
state (mu::script::parser::expression_state::values),
routine (routine_a),
element (0)
{
}

void mu::script::parser::expression::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
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
            auto expression_l (expression_m);
            auto position (expression_l->dependencies.size ());
            expression_l->dependencies.resize (position + 1);
            routine.cluster.map.fill_reference (token->string, context,
                [expression_l, position]
                (mu::core::node * node_a)
                {
                    assert (dynamic_cast <mu::script::operation *> (node_a) != nullptr);
                    expression_l->dependencies [position] = static_cast <mu::script::operation *> (node_a);
                }
            );
            break;
        }
        case mu::script::parser::expression_state::name:
            routine.cluster.map.insert_local (routine.cluster.parser.errors, token->string, expression_m, context);
            break;
        case mu::script::parser::expression_state::have_name:
            unexpected_token (routine.cluster.parser, token, context);
            break;
        case mu::script::parser::expression_state::elements:
            routine.cluster.map.insert_local(routine.cluster.parser.errors, token->string, new (GC) mu::script::runtime::selection (expression_m, element), context);
            ++element;
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::expression::operator () (mu::io::tokens::left_square * token)
{
    auto state_l (new (GC) mu::script::parser::expression (routine));
    expression_m->dependencies.push_back (state_l->expression_m);
    routine.cluster.parser.state.push (state_l);
}

void mu::script::parser::expression::operator () (mu::io::tokens::right_square * token)
{
    routine.cluster.parser.state.pop ();
}

void mu::script::parser::expression::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::script::parser::expression::operator () (mu::io::tokens::parameters * token)
{
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::script::parser::expression::operator () (mu::io::tokens::value * token)
{
    switch (state)
    {
        case mu::script::parser::expression_state::values:
            expression_m->dependencies.push_back (new (GC) mu::script::runtime::fixed (token->node));
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