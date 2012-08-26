#include <mu/script/builder.h>

#include <boost/bind.hpp>

#include <mu/io/ast_cluster.h>
#include <mu/io/ast_node.h>
#include <mu/io/ast_expression.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>
#include <mu/script/cluster_node.h>
#include <mu/io/keywording_extensions.h>

#include <gc_cpp.h>

mu::script::builder::builder ():
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
        }
        ),
keywording (errors,
            [this]
            (mu::io::tokens::token * token)
            {
                parser (token);
            }, new (GC) mu::io::keywording::extensions),
lexer (errors,
       [this]
       (mu::io::tokens::token * token)
       {
           keywording (token);
       })
{
}

mu::script::builder::builder (mu::io::keywording::extensions * extensions_a):
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
        }
        ),
keywording (errors,
            [this, extensions_a]
            (mu::io::tokens::token * token)
            {
                parser (token);
            }, extensions_a),
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