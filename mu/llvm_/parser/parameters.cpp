#include <mu/llvm_/parser/parameters.h>

#include <mu/io/tokens/token.h>
#include <mu/llvm_/parser/routine.h>
#include <mu/llvm_/parser/parser.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/left_square.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/value.h>
#include <mu/io/tokens/identifier.h>
#include <mu/llvm_/parser/cluster.h>
#include <mu/llvm_/type/node.h>
#include <mu/core/errors/error_target.h>
#include <mu/llvm_/parser/error.h>
#include <mu/io/tokens/right_square.h>
#include <mu/llvm_/function/node.h>
#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/set_type/node.h>
#include <mu/llvm_/void_type/node.h>
#include <mu/llvm_/parser/error.h>
#include <mu/llvm_/ast_routine.h>
#include <mu/llvm_/ast_parameter.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>

#include <gc_cpp.h>

mu::llvm_::parser::parameters::parameters (mu::llvm_::parser::routine & routine_a):
routine (routine_a),
state (mu::llvm_::parser::parameters_state::name),
position (0)
{
}

void mu::llvm_::parser::parameters::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    context = context_a;
    (*token_a) (this);
}

void mu::llvm_::parser::parameters::operator () (mu::io::tokens::divider * token)
{
    switch (state)
    {
        case mu::llvm_::parser::parameters_state::results:
            break;
        case mu::llvm_::parser::parameters_state::parameters:
            state = mu::llvm_::parser::parameters_state::results;
        case mu::llvm_::parser::parameters_state::name:
            unexpected_token (routine.cluster.parser, token, context);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::llvm_::parser::parameters::operator () (mu::io::tokens::identifier * token)
{
    switch (state)
    {
        case mu::llvm_::parser::parameters_state::results:
        case mu::llvm_::parser::parameters_state::parameters:
            unexpected_token (routine.cluster.parser, token, context);
            break;
        case mu::llvm_::parser::parameters_state::name:
        {
            state = mu::llvm_::parser::parameters_state::parameters;
            auto position_l (position);
            routine.cluster.map.insert_local (routine.cluster.parser.errors, token->string, new (GC) mu::llvm_::ast::parameter (position_l), context);
            position = position_l + 1;
        }
            break;
        default:
            assert (false);
            break;
    }
}

void mu::llvm_::parser::parameters::operator () (mu::io::tokens::left_square * token)
{
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::llvm_::parser::parameters::operator () (mu::io::tokens::right_square * token)
{
    switch (state)
    {
        case mu::llvm_::parser::parameters_state::results:
        case mu::llvm_::parser::parameters_state::name:
            routine.cluster.parser.state.pop ();
            break;
        case mu::llvm_::parser::parameters_state::parameters:
            unexpected_token (routine.cluster.parser, token, context);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::llvm_::parser::parameters::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (routine.cluster.parser, token, context);
}

void mu::llvm_::parser::parameters::operator () (mu::io::tokens::value * token)
{
    switch (state)
    {
        case mu::llvm_::parser::parameters_state::results:
        {
            auto type (dynamic_cast <mu::llvm_::type::node *> (token->node));
            if (type != nullptr)
            {
                routine.routine_m->results.push_back (type);
            }
            else                
            {
                mu::stringstream message;
                message << U"Unexpected value type: ";
                message << token->node->name ();
                message << U", expecting mu::llvm_::type::node";
                routine.cluster.parser.errors (message.str ());
                routine.cluster.parser.state.push (new (GC) mu::llvm_::parser::error);
            }
        }
            break;
        case mu::llvm_::parser::parameters_state::parameters:
        {
            auto type (dynamic_cast <mu::llvm_::type::node *> (token->node));
            if (type != nullptr)
            {
                state = mu::llvm_::parser::parameters_state::name;
                routine.routine_m->types.push_back (type);
            }
            else
            {
                mu::stringstream message;
                message << U"Unexpected value type: ";
                message << token->node->name ();
                message << U", expecting mu::llvm_::type::node";
                routine.cluster.parser.errors (message.str ());
                routine.cluster.parser.state.push (new (GC) mu::llvm_::parser::error);
            }
        }
            break;
        case mu::llvm_::parser::parameters_state::name:
            unexpected_token (routine.cluster.parser, token, context);
            break;
        default:
            assert (false);
            break;
    }
}