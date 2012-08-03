#include <mu/script/parser/cluster.h>

#include <mu/io/tokens/token.h>
#include <mu/script/parser/parser.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/right_square.h>
#include <mu/io/tokens/parameters.h>
#include <mu/io/tokens/value.h>
#include <mu/script/parser/routine.h>
#include <mu/script/cluster/node.h>

#include <gc_cpp.h>

mu::script::parser::cluster::cluster (mu::script::parser::parser & parser_a):
parser (parser_a),
cluster_m (new (GC) mu::script::cluster::node)
{
}

void mu::script::parser::cluster::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    context = context_a;
    (*token_a) (this);
}

void mu::script::parser::cluster::operator () (mu::io::tokens::divider * token)
{
    unexpected_token (parser, token, context);
}

void mu::script::parser::cluster::operator () (mu::io::tokens::identifier * token)
{
    unexpected_token (parser, token, context);
}

void mu::script::parser::cluster::operator () (mu::io::tokens::left_square * token)
{
    parser.state.push (new (GC) mu::script::parser::routine (*this));
}

void mu::script::parser::cluster::operator () (mu::io::tokens::right_square * token)
{
    unexpected_token (parser, token, context);
}

void mu::script::parser::cluster::operator () (mu::io::tokens::stream_end * token)
{
    parser.target (cluster_m);
    cluster_m = new (GC) mu::script::cluster::node;
}

void mu::script::parser::cluster::operator () (mu::io::tokens::parameters * token)
{
    unexpected_token (parser, token, context);    
}

void mu::script::parser::cluster::operator () (mu::io::tokens::value * token)
{
    unexpected_token (parser, token, context);
}