#include "expression_list.h"

#include <lambda_p/core/expression_list_iterator.h>

lambda_p::core::expression_iterator lambda_p::core::expression_list::begin ()
{
	return lambda_p::core::expression_iterator (new lambda_p::core::expression_list_iterator (*this, false));
}

lambda_p::core::expression_iterator lambda_p::core::expression_list::end ()
{
	return lambda_p::core::expression_iterator (new lambda_p::core::expression_list_iterator (*this, true));
}

bool lambda_p::core::expression_list::resolved ()
{
	bool result (true);
	for (auto i (contents.begin ()), j (contents.end ()); i != j; ++i)
	{
		result = *i != nullptr && (*i)->resolved ();
	}
	return result;
}