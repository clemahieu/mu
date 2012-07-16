#include <mu/script/unit/operation.h>

bool mu::script::unit::operation::operator () (mu::script::context & context_a)
{
	return true;
}

mu::string mu::script::unit::operation::name ()
{
	return mu::string (U"mu::script::unit::operation");
}