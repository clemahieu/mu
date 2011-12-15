#include "gather.h"

#include <lambda_p/core/target.h>

lambda_p::core::gather::gather (boost::shared_ptr <lambda_p::core::target> target_a, size_t size_a)
	: arguments (size_a),
	target (target_a),
	remaining (size_a)
{
	assert (target_a != nullptr && L"Null target");
}

void lambda_p::core::gather::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments_a)
{
	arguments.insert (arguments.end (), arguments_a.begin (), arguments_a.end ());
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