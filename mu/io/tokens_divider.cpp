#include <mu/io/tokens_divider.h>
#include <mu/io/tokens_visitor.h>

#include <iostream>

mu::io::tokens::divider::divider (mu::io::context const & context_a):
mu::io::tokens::token (context_a)
{
}

mu::string mu::io::tokens::divider::token_name () const
{
	return mu::string (U"divider");
}

void mu::io::tokens::divider::operator () (mu::io::tokens::visitor * visitor_a) const
{
	(*visitor_a) (*this);
}