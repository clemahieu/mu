#include <mu/llvm_/parser/parameters.h>

#include <mu/io/tokens/token.h>
#include <mu/llvm_/parser/routine.h>
#include <mu/llvm_/parser/parser.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/left_square.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/parameters.h>
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

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>

#include <gc_cpp.h>

mu::llvm_::parser::parameters::parameters (mu::llvm_::parser::routine & routine_a):
routine (routine_a),
state (mu::llvm_::parser::parameters_state::name)
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
            state = mu::llvm_::parser::parameters_state::parameters;
            names.push_back (token->string);
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
        {
            if (results.size () == 0)
            {
                auto function_type_l (new (GC) mu::llvm_::function_type::node (routine.cluster.parser.ctx.context, types, new (GC) mu::llvm_::void_type::node (routine.cluster.parser.ctx.context)));
                auto function_l (llvm::Function::Create (function_type_l->function_type (), llvm::GlobalValue::LinkageTypes::ExternalLinkage));
                routine.routine_m->function = new (GC) mu::llvm_::function::node (function_l, function_type_l);
            }
            else if (results.size () == 1)
            {
                auto function_type_l (new (GC) mu::llvm_::function_type::node (routine.cluster.parser.ctx.context, types, results [0]));
                auto function_l (llvm::Function::Create (function_type_l->function_type (), llvm::GlobalValue::LinkageTypes::ExternalLinkage));
                routine.routine_m->function = new (GC) mu::llvm_::function::node (function_l, function_type_l);
            }
            else
            {
                auto function_type_l (new (GC) mu::llvm_::function_type::node (routine.cluster.parser.ctx.context, types, new (GC) mu::llvm_::set_type::node (routine.cluster.parser.ctx.context, results)));
                auto function_l (llvm::Function::Create (function_type_l->function_type (), llvm::GlobalValue::LinkageTypes::ExternalLinkage));
                routine.routine_m->function = new (GC) mu::llvm_::function::node (function_l, function_type_l);
            }
            routine.cluster.parser.state.pop ();
        }
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

void mu::llvm_::parser::parameters::operator () (mu::io::tokens::parameters * token)
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
                results.push_back (type);
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
                types.push_back (type);
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