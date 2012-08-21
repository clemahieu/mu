#include <mu/llvm_/parser/cluster.h>

#include <mu/io/tokens/token.h>
#include <mu/llvm_/parser/parser.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/right_square.h>
#include <mu/io/tokens/parameters.h>
#include <mu/io/tokens/value.h>
#include <mu/llvm_/parser/routine.h>
#include <mu/llvm_/ast_cluster.h>

#include <gc_cpp.h>

mu::llvm_::parser::cluster::cluster (mu::llvm_::parser::parser & parser_a):
parser (parser_a),
cluster_m (new (GC) mu::llvm_::ast::cluster)
{
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    context = context_a;
    (*token_a) (this);
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::divider * token)
{
    unexpected_token (parser, token, context);
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::identifier * token)
{
    unexpected_token (parser, token, context);
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::left_square * token)
{
    auto state_l (new (GC) mu::llvm_::parser::routine (*this));
    parser.state.push (state_l);
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::right_square * token)
{
    unexpected_token (parser, token, context);
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::stream_end * token)
{
    auto failed (map.finalize (parser.errors));
    if (!failed)
    {
        parser.target (cluster_m);
    }
    cluster_m = new (GC) mu::llvm_::ast::cluster;
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::parameters * token)
{
    unexpected_token (parser, token, context);    
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::value * token)
{
    unexpected_token (parser, token, context);
}