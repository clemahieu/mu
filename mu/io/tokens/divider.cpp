#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/visitor.h>

#include <iostream>

mu::string mu::io::tokens::divider::token_name ()
{
	return mu::string (U"divider");
}

void mu::io::tokens::divider::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}