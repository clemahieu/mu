#include "expression.h"

#include <lambda_p/core/expression_list_iterator.h>
#include <lambda_p/core/expression_leaf_iterator.h>

lambda_p::core::expression_iterator lambda_p::core::expression::begin ()
{
	lambda_p::core::expression_iterator result (contents.empty () ?
		lambda_p::core::expression_iterator (new lambda_p::core::expression_leaf_iterator (this, false)) :
		lambda_p::core::expression_iterator (new lambda_p::core::expression_list_iterator (false, contents.begin (), contents.end ())));
	return result;
}

lambda_p::core::expression_iterator lambda_p::core::expression::end ()
{
	lambda_p::core::expression_iterator result (contents.empty () ?
		lambda_p::core::expression_iterator (new lambda_p::core::expression_leaf_iterator (this, true)) :
		lambda_p::core::expression_iterator (new lambda_p::core::expression_list_iterator (true, contents.end (), contents.end ())));
	return result;
}

bool lambda_p::core::expression::resolved ()
{
	bool result (true);
	for (auto i (contents.begin ()), j (contents.end ()); i != j; ++i)
	{
		result = *i != nullptr && (*i)->resolved ();
	}
	return result;
}