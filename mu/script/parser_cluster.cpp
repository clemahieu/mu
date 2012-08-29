#include <mu/script/parser_cluster.h>

#include <mu/io/tokens_implementor.h>
#include <mu/script/parser_parser.h>
#include <mu/script/parser_routine.h>
#include <mu/script/ast_cluster.h>
#include <mu/script/parser_scope_node.h>

#include <gc_cpp.h>

mu::script::parser::cluster::cluster (mu::script::parser::parser & parser_a):
parser (parser_a),
cluster_m (new (GC) mu::script::ast::cluster)
{
    for (auto i (parser_a.scope->injected.begin ()), j (parser_a.scope->injected.end ()); i != j; ++i)
    {
        map.insert_cluster_scope (parser.errors, i->first, i->second, mu::io::context ());
    }
}

void mu::script::parser::cluster::operator () (mu::io::tokens::token * token_a)
{
    (*token_a) (this);
}

void mu::script::parser::cluster::operator () (mu::io::tokens::divider * token)
{
    unexpected_token (parser, token);
}

void mu::script::parser::cluster::operator () (mu::io::tokens::identifier * token)
{
    unexpected_token (parser, token);
}

void mu::script::parser::cluster::operator () (mu::io::tokens::left_square * token)
{
    auto state_l (new (GC) mu::script::parser::routine (*this));
    parser.state.push (state_l);
}

void mu::script::parser::cluster::operator () (mu::io::tokens::right_square * token)
{
    unexpected_token (parser, token);
}

void mu::script::parser::cluster::operator () (mu::io::tokens::stream_end * token)
{
    auto failed (map.finalize (parser.errors));
    if (!failed)
    {
        parser.target (cluster_m);
    }
    cluster_m = new (GC) mu::script::ast::cluster;
}

void mu::script::parser::cluster::operator () (mu::io::tokens::value * token)
{
    unexpected_token (parser, token);
}