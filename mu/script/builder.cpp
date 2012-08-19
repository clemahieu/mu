#include <mu/script/builder.h>

#include <boost/bind.hpp>

#include <mu/script/ast/extension.h>
#include <mu/io/ast/cluster.h>
#include <mu/io/ast/node.h>
#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>
#include <mu/script/cluster/node.h>
#include <mu/io/keywording/extensions.h>

#include <gc_cpp.h>

mu::script::builder::builder ():
synthesizer (
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
        }
        ),
keywording (errors,
            [this]
            (mu::io::tokens::token * token, mu::io::debugging::context context)
            {
                parser (token, context);
            }, new (GC) mu::io::keywording::extensions),
lexer (errors,
       [this]
       (mu::io::tokens::token * token, mu::io::debugging::context context)
       {
           keywording (token, context);
       })
{
}

mu::script::builder::builder (mu::io::keywording::extensions * extensions_a):
synthesizer (
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
        }
        ),
keywording (errors,
            [this, extensions_a]
            (mu::io::tokens::token * token, mu::io::debugging::context context)
            {
                parser (token, context);
            }, extensions_a),
lexer (errors,
       [this]
       (mu::io::tokens::token * token, mu::io::debugging::context context)
       {
           keywording (token, context);
       })
{
}

void mu::script::builder::operator () (mu::io::lexer::context const & context_a)
{
	lexer (context_a);
}