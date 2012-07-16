#include <mu/io/tokens/parameters.h>

#include <mu/io/tokens/visitor.h>

mu::string mu::io::tokens::parameters::token_name ()
{
	return mu::string (U"parameters");
}

void mu::io::tokens::parameters::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}