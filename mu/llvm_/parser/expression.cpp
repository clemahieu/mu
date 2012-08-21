#include <mu/llvm_/parser/expression.h>

#include <mu/script/runtime/expression.h>
#include <mu/io/tokens/divider.h>
#include <mu/llvm_/parser/routine.h>
#include <mu/llvm_/parser/cluster.h>
#include <mu/io/tokens/identifier.h>
#include <mu/llvm_/parser/parser.h>
#include <mu/script/runtime/selection.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/parameters.h>
#include <mu/io/tokens/value.h>
#include <mu/script/runtime/fixed.h>
#include <mu/io/tokens/right_square.h>
#include <mu/script/runtime/reference.h>

#include <gc_cpp.h>

#include <assert.h>

mu::llvm_::parser::expression::expression (mu::llvm_::parser::routine & routine_a):
state (mu::llvm_::parser::expression_state::values),
routine (routine_a),
element (~0)
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
        case mu::llvm_::parser::expression_state::name:
            routine.cluster.map.insert_local (routine.cluster.parser.errors, token->string, new (GC) mu::script::runtime::reference (expression_m), context);
            state = mu::script::parser::expression_state::have_name;
            break;
        case mu::llvm_::parser::expression_state::have_name:
            unexpected_token (routine.cluster.parser, token, context);
            break;
        case mu::llvm_::parser::expression_state::elements:
            
            break;
        default:
            assert (false);
            break;
    }
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::left_square * token)
{
    auto expression_l (expression_m);
    auto state_l (new (GC) mu::script::parser::expression (routine,
                                                           [expression_l]
                                                           (mu::script::runtime::expression * expression_a)
                                                           {
                                                               expression_l->dependencies.push_back (new (GC) mu::script::runtime::reference (expression_a));
                                                           }));
    routine.cluster.parser.state.push (state_l);
}

void mu::llvm_::parser::expression::operator () (mu::io::tokens::right_square * token)
{
    switch (state)
    {
        case mu::script::parser::expression_state::values:
            target (expression_m);
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