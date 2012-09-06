#include <mu/io/tokens_right_square.h>

#include <mu/io/tokens_visitor.h>

mu::io::tokens::right_square::right_square (mu::io::context const & context_a):
mu::io::tokens::token (context_a)
{
}

mu::string mu::io::tokens::right_square::token_name () const
{
	return mu::string (U"right square");
}

void mu::io::tokens::right_square::operator () (mu::io::tokens::visitor * visitor_a) const
{
	(*visitor_a) (*this);
}