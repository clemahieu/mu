#include "expression.h"

void lambda_p::core::expression::add (boost::shared_ptr <lambda_p::core::expression> other)
{
	contents.insert (other->contents.begin (), other->contents.end ());
}