#include <mu/io/ast_value.h>

#include <mu/io/ast_visitor.h>

mu::io::ast::value::value (mu::core::node * node_a, mu::io::context const & context_a):
node (context_a),
node_m (node_a)
{
}


void mu::io::ast::value::operator () (mu::io::ast::visitor * visitor_a)
{
    (*visitor_a) (this);
}

mu::string mu::io::ast::value::name ()
{
    return mu::string (U"value");
}