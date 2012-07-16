#include <mu/io/tokens/left_square.h>

#include <mu/io/tokens/visitor.h>

mu::string mu::io::tokens::left_square::token_name ()
{
	return mu::string (U"left square");
}

void mu::io::tokens::left_square::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}