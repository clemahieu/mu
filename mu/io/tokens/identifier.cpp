#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/visitor.h>

#include <iostream>

mu::io::tokens::identifier::identifier (mu::io::context const & context_a, mu::string string_a):
mu::io::tokens::token (context_a),
string (string_a)
{
}

mu::string mu::io::tokens::identifier::token_name ()
{
	return mu::string (U"identifier");
}

void mu::io::tokens::identifier::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}