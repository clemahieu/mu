#include <mu/io/tokens/value.h>

#include <mu/io/tokens/visitor.h>

mu::io::tokens::value::value (mu::core::node * node_a)
    : node (node_a)
{
}

mu::string mu::io::tokens::value::token_name ()
{
    return mu::string (U"value");
}

void mu::io::tokens::value::operator () (mu::io::tokens::visitor * visitor_a)
{
    (*visitor_a) (this);
}