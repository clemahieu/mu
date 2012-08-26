#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/visitor.h>

#include <iostream>

mu::io::tokens::divider::divider (mu::io::context const & context_a):
mu::io::tokens::token (context_a)
{
}

mu::string mu::io::tokens::divider::token_name ()
{
	return mu::string (U"divider");
}

void mu::io::tokens::divider::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}