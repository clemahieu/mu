#include "gather.h"

#include <lambda_p/core/input.h>

lambda_p::core::gather::gather (boost::shared_ptr <lambda_p::core::input> target_a, size_t size_a)
	: arguments (size_a),
	target (target_a),
	remaining (size_a)
{
	assert (target_a != nullptr && L"Null target");
}

void lambda_p::core::gather::operator () (boost::shared_ptr <lambda_p::core::expression> expression_a, size_t index_a)
{
	assert (expression_a.get () != nullptr && L"Null expression");
	assert (arguments.size () > index_a && L"Out of bounds");
	assert (arguments [index_a].get () == nullptr && L"Already set");
	arguments [index_a] = expression_a;
	--remaining;
	if (remaining == 0)
	{
		(*target) (arguments);
		remaining = arguments.size ();
		for (auto i (arguments.begin ()), j (arguments.end ()); i != j; ++i)
		{
			i->reset ();
		}
	}
}