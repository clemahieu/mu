#include "entry.h"

#include <lambda_p/core/fixed.h>

lambda_p::core::entry::entry (boost::shared_ptr <lambda_p::core::target> next_a)
	: next (next_a)
{
}

void lambda_p::core::entry::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments)
{
	for (auto i (fixed_parameters.begin ()), j (fixed_parameters.end ()); i != j; ++i)
	{
		(*(*i)) ();
	}
	(*next) (arguments);
}