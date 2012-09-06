#include <mu/io/tokens_value.h>

#include <mu/io/tokens_visitor.h>

mu::io::tokens::value::value (mu::io::context const & context_a, mu::core::node * node_a):
mu::io::tokens::token (context_a),
node (node_a)
{
}

mu::string mu::io::tokens::value::token_name () const
{
    return mu::string (U"value");
}

void mu::io::tokens::value::operator () (mu::io::tokens::visitor * visitor_a) const
{
    (*visitor_a) (*this);
}