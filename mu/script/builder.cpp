#include <mu/script/builder.h>

#include <boost/bind.hpp>

#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>
#include <mu/script/cluster_node.h>
#include <mu/io/keywording_extensions.h>
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
keywording (errors,
            [this]
            (mu::io::tokens::token * token)
            {
                parser (token);
            }, scope->extensions),
lexer (errors,
       [this]
       (mu::io::tokens::token * token)
       {
           keywording (token);
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
keywording (errors,
            [this]
            (mu::io::tokens::token * token)
            {
                parser (token);
            }, scope_a->extensions),
lexer (errors,
       [this]
       (mu::io::tokens::token * token)
       {
           keywording (token);
       })
{
}

void mu::script::builder::operator () (mu::io::lexer::context const & context_a)
{
	lexer (context_a);
}