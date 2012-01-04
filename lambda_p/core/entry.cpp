#include "entry.h"

#include <lambda_p/core/fixed.h>
#include <lambda_p/core/tee.h>
#include <lambda_p/core/explode.h>

lambda_p::core::entry::entry (boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: next (new lambda_p::core::tee),
	errors (errors_a)
{
}

void lambda_p::core::entry::operator () (std::vector <boost::shared_ptr <lambda_p::core::node>> & arguments)
{
	for (auto i (fixed.begin ()), j (fixed.end ()); i != j; ++i)
	{
		(*(*i)) ();
	}
	auto explode (boost::shared_ptr <lambda_p::core::node> (new lambda_p::core::explode (arguments, errors)));
	std::vector <boost::shared_ptr <lambda_p::core::node>> arguments_l;
	arguments_l.push_back (explode);
	(*next) (arguments_l);
}