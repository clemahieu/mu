#include <mu/script/builder.h>

#include <boost/bind.hpp>

#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>
#include <mu/script/cluster_node.h>
#include <mu/io/analyzer_extensions.h>
#include <mu/script/parser_scope_node.h>

#include <gc_cpp.h>

mu::script::builder::builder ():
scope (new (GC) mu::script::parser_scope::node),
synthesizer (errors,
             [this]
             (mu::script::cluster::node * cluster_a)
             {
                 clusters.push_back (cluster_a);
             }),
parser (errors,
        [this]
        (mu::script::ast::cluster * cluster_a)
        {
            synthesizer (cluster_a);
        }, scope),
analyzer (errors,
            [this]
            (mu::io::tokens::token const & token)
            {
                parser (token);
            }, scope->extensions),
lexer (errors,
       [this]
       (mu::io::tokens::token const & token)
       {
           analyzer (token);
       })
{
}

mu::script::builder::builder (mu::script::parser_scope::node * scope_a):
scope (scope_a),
synthesizer (errors,
             [this]
             (mu::script::cluster::node * cluster_a)
             {
                 clusters.push_back (cluster_a);
             }),
parser (errors,
        [this]
        (mu::script::ast::cluster * cluster_a)
        {
            synthesizer (cluster_a);
        }, scope_a),
analyzer (errors,
            [this]
            (mu::io::tokens::token const & token)
            {
                parser (token);
            }, scope_a->extensions),
lexer (errors,
       [this]
       (mu::io::tokens::token const & token)
       {
           analyzer (token);
       })
{
}

void mu::script::builder::operator () (mu::io::lexer::context const & context_a)
{
	lexer (context_a);
}