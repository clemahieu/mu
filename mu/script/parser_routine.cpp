#include <mu/script/parser_routine.h>

#include <mu/io/tokens_implementor.h>
#include <mu/script/parser_parser.h>
#include <mu/script/parser_body.h>
#include <mu/script/parser_parameters.h>
#include <mu/script/ast_routine.h>
#include <mu/script/runtime_expression.h>
#include <mu/script/parser_cluster.h>
#include <mu/script/ast_cluster.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/runtime_reference.h>
#include <mu/script/tokens_keyword_if.h>
#include <mu/script/parser_keyword_if.h>
#include <mu/script/ast_if_expression.h>

#include <assert.h>

#include <gc_cpp.h>

mu::script::parser::routine::routine (mu::script::parser::cluster & cluster_a):
state (mu::script::parser::routine_state::name),
parameters (0),
cluster (cluster_a),
routine_m (new (GC) mu::script::ast::routine)
{
}

void mu::script::parser::routine::operator () (mu::io::tokens::token * token_a)
{
    (*token_a) (this);
}

void mu::script::parser::routine::operator () (mu::io::tokens::divider * token)
{
    switch (state)
    {
        case mu::script::parser::routine_state::parameters:
            state = mu::script::parser::routine_state::body;
            break;
        case mu::script::parser::routine_state::name:
        case mu::script::parser::routine_state::body:
        case mu::script::parser::routine_state::have_body:
            unexpected_token (cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::routine::operator () (mu::io::tokens::identifier * token)
{
    switch (state)
    {
        case mu::script::parser::routine_state::name:
            state = mu::script::parser::routine_state::parameters;
            routine_m->name = token->string;
            cluster.map.insert_cluster_scope (cluster.parser.errors, token->string, routine_m, token->context);
            break;
        case mu::script::parser::routine_state::parameters:
        case mu::script::parser::routine_state::body:
        case mu::script::parser::routine_state::have_body:
            unexpected_token (cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::routine::operator () (mu::io::tokens::left_square * token)
{
    switch (state)
    {
        case mu::script::parser::routine_state::parameters:
            state = mu::script::parser::routine_state::body;
            cluster.parser.state.push (new (GC) mu::script::parser::parameters (*this));
            break;
        case mu::script::parser::routine_state::body:
        {
            state = mu::script::parser::routine_state::have_body;
            auto state_l (new (GC) mu::script::parser::body (*this, routine_m->body));
            cluster.parser.state.push (state_l);
            break;
        }
        case mu::script::parser::routine_state::have_body:
        case mu::script::parser::routine_state::name:
            unexpected_token (cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::routine::operator () (mu::io::tokens::right_square * token)
{
    switch (state)
    {
        case mu::script::parser::routine_state::have_body:
            cluster.cluster_m->routines.push_back (routine_m);
            cluster.map.free_locals ();
            cluster.parser.state.pop ();
            break;
        case mu::script::parser::routine_state::body:
        case mu::script::parser::routine_state::name:
        case mu::script::parser::routine_state::parameters:
            unexpected_token (cluster.parser, token);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::routine::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (cluster.parser, token);
}

void mu::script::parser::routine::operator () (mu::io::tokens::value * token)
{
    auto if_l (dynamic_cast <mu::script::tokens::keyword_if *> (token->node));
    if (if_l != nullptr)
    {
        auto expression_l (new (GC) mu::script::ast::if_expression);
        
        auto state_l (new (GC) mu::script::parser::keyword_if (*this, expression_l));
        cluster.parser.state.push (state_l);
    }
    else
    {
        unexpected_token (cluster.parser, token);        
    }
}