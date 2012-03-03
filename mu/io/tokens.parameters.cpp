#include "tokens.parameters.h"
#include <mu/io/tokens.visitor.h>

std::wstring mu::io::tokens::parameters::token_name ()
{
	return std::wstring (L"parameters");
}

void mu::io::tokens::parameters::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (this);
}
