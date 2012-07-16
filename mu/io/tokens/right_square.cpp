#include <mu/io/tokens/right_square.h>

#include <mu/io/tokens/visitor.h>

mu::string mu::io::tokens::right_square::token_name ()
{
	return mu::string (U"right square");
}

void mu::io::tokens::right_square::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}