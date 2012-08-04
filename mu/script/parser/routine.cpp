#include <mu/script/parser/routine.h>

#include <mu/script/parser/parser.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/right_square.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/parameters.h>
#include <mu/io/tokens/value.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/left_square.h>
#include <mu/script/parser/body.h>
#include <mu/script/parser/parameters.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/runtime/expression.h>
#include <mu/script/parser/cluster.h>
#include <mu/script/cluster/node.h>

#include <assert.h>

#include <gc_cpp.h>

mu::script::parser::routine::routine (mu::script::parser::cluster & cluster_a):
state (mu::script::parser::routine_state::name),
parameters (0),
cluster (cluster_a),
parameters_m (new (GC) mu::script::runtime::expression),
routine_m (new (GC) mu::script::runtime::routine (parameters_m))
{
}

void mu::script::parser::routine::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    context = context_a;
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
            unexpected_token (cluster.parser, token, context);
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
            name = token->string;
            break;
        case mu::script::parser::routine_state::parameters:
        case mu::script::parser::routine_state::body:
            unexpected_token (cluster.parser, token, context);
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
            cluster.parser.state.push (new (GC) mu::script::parser::body (*this));
            break;
        case mu::script::parser::routine_state::name:
            unexpected_token (cluster.parser, token, context);
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
        case mu::script::parser::routine_state::body:
            cluster.map.insert_global (cluster.parser.errors, name, routine_m, context);
            cluster.cluster_m->routines.push_back (routine_m);
            cluster.cluster_m->names [name] = routine_m;
            cluster.map.free_locals ();
            cluster.parser.state.pop ();
            break;
        case mu::script::parser::routine_state::name:
        case mu::script::parser::routine_state::parameters:
            unexpected_token (cluster.parser, token, context);
            break;
        default:
            assert (false);
            break;
    }
}

void mu::script::parser::routine::operator () (mu::io::tokens::stream_end * token)
{
    unexpected_token (cluster.parser, token, context);
}

void mu::script::parser::routine::operator () (mu::io::tokens::parameters * token)
{
    unexpected_token (cluster.parser, token, context);
}

void mu::script::parser::routine::operator () (mu::io::tokens::value * token)
{
    unexpected_token (cluster.parser, token, context);
}