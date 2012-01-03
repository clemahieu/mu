#include "entry.h"

#include <lambda_p/core/fixed.h>
#include <lambda_p/core/tee.h>

lambda_p::core::entry::entry ()
	: next (new lambda_p::core::tee)
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