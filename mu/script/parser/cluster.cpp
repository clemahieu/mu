#include <mu/script/parser/cluster.h>

#include <mu/io/tokens/implementor.h>
#include <mu/script/parser/parser.h>
#include <mu/script/parser/routine.h>
#include <mu/script/ast_cluster.h>

#include <gc_cpp.h>

mu::script::parser::cluster::cluster (mu::script::parser::parser & parser_a):
parser (parser_a),
cluster_m (new (GC) mu::script::ast::cluster)
{
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