#include <mu/io/tokens_left_square.h>

#include <mu/io/tokens_visitor.h>

mu::io::tokens::left_square::left_square (mu::io::context const & context_a):
mu::io::tokens::token (context_a)
{
}

mu::string mu::io::tokens::left_square::token_name ()
{
	return mu::string (U"left square");
}

void mu::io::tokens::left_square::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}