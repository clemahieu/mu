#include <mu/llvm_/parser_cluster.h>

#include <mu/io/tokens_implementor.h>
#include <mu/llvm_/parser_parser.h>
#include <mu/llvm_/parser_routine.h>
#include <mu/llvm_/ast_cluster.h>
#include <mu/io/analyzer_extensions.h>

#include <gc_cpp.h>

mu::llvm_::parser::cluster::cluster (mu::llvm_::parser::parser & parser_a):
parser (parser_a),
cluster_m (new (GC) mu::llvm_::ast::cluster),
scope (*(new (GC) mu::io::analyzer::extensions))
{
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::token * token_a)
{
    (*token_a) (this);
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::divider const & token)
{
    unexpected_token (parser, token);
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::identifier const & token)
{
    unexpected_token (parser, token);
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::left_square const & token)
{
    auto state_l (new (GC) mu::llvm_::parser::routine (*this));
    parser.state.push (state_l);
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::right_square const & token)
{
    unexpected_token (parser, token);
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::stream_end const & token)
{
    auto failed (scope.end (parser.errors));
    if (!failed)
    {
        parser.target (cluster_m);
    }
    cluster_m = new (GC) mu::llvm_::ast::cluster;
}

void mu::llvm_::parser::cluster::operator () (mu::io::tokens::value const & token)
{
    unexpected_token (parser, token);
}