#include <mu/llvm_/parser_routine.h>

#include <mu/io/tokens_implementor.h>
#include <mu/llvm_/parser_parser.h>
#include <mu/llvm_/parser_body.h>
#include <mu/llvm_/parser_parameters.h>
#include <mu/llvm_/parser_cluster.h>
#include <mu/llvm_/cluster_node.h>
#include <mu/core/errors/error_list.h>
#include <mu/llvm_/function_node.h>
#include <mu/llvm_/ast_routine.h>
#include <mu/llvm_/ast_cluster.h>
#include <mu/llvm_/function_type_node.h>
#include <mu/llvm_/void_type_node.h>

#include <assert.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>

#include <gc_cpp.h>

mu::llvm_::parser::routine::routine (mu::llvm_::parser::cluster & cluster_a):
state (mu::llvm_::parser::routine_state::name),
cluster (cluster_a),
routine_m (new (GC) mu::llvm_::ast::routine)
{
}

void mu::llvm_::parser::routine::operator () (mu::io::tokens::token * token_a)
{
    (*token_a) (this);
}

void mu::llvm_::parser::routine::operator () (mu::io::tokens::divider * token)
{
    switch (state)
    {
        case mu::llvm_::parser::routine_state::parameters:
            state = mu::llvm_::parser::routine_state::body;
            break;
        case mu::llvm_::parser::routine_state::name:
        case mu::llvm_::parser::routine_state::body:
        case mu::llvm_::parser::routine_state::have_body:
            unexpected_token (cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::llvm_::parser::routine::operator () (mu::io::tokens::identifier * token)
{
    switch (state)
    {
        case mu::llvm_::parser::routine_state::name:
            cluster.map.insert_cluster_scope (cluster.parser.errors, token->string, routine_m, token->context);
            routine_m->name = token->string;
            state = mu::llvm_::parser::routine_state::parameters;
            break;
        case mu::llvm_::parser::routine_state::parameters:
        case mu::llvm_::parser::routine_state::body:
        case mu::llvm_::parser::routine_state::have_body:
            unexpected_token (cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::llvm_::parser::routine::operator () (mu::io::tokens::left_square * token)
{
    switch (state)
    {
        case mu::llvm_::parser::routine_state::parameters:
            state = mu::llvm_::parser::routine_state::body;
            cluster.parser.state.push (new (GC) mu::llvm_::parser::parameters (*this));
            break;
        case mu::llvm_::parser::routine_state::body:
        {
            state = mu::llvm_::parser::routine_state::have_body;
            auto state_l (new (GC) mu::llvm_::parser::body (*this));
            cluster.parser.state.push (state_l);
            break;
        }
        case mu::llvm_::parser::routine_state::have_body:
        case mu::llvm_::parser::routine_state::name:
            unexpected_token (cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::llvm_::parser::routine::operator () (mu::io::tokens::right_square * token)
{
    switch (state)
    {
        case mu::llvm_::parser::routine_state::have_body:
            cluster.cluster_m->routines.push_back (routine_m);
            cluster.map.free_locals ();
            cluster.parser.state.pop ();
            break;
        case mu::llvm_::parser::routine_state::body:
        case mu::llvm_::parser::routine_state::name:
        case mu::llvm_::parser::routine_state::parameters:
            unexpected_token (cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::llvm_::parser::routine::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (cluster.parser, token);
}

void mu::llvm_::parser::routine::operator () (mu::io::tokens::value * token)
{
    unexpected_token (cluster.parser, token);
}