#include "entry.h"

#include <lambda_p/core/fixed.h>

void lambda_p::core::entry::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments)
{
	for (auto i (fixed_parameters.begin ()), j (fixed_parameters.end ()); i != j; ++i)
	{
		(*(*i)) ();
	}
	(*next) (arguments);
}