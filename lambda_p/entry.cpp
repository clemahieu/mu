#include "entry.h"

#include <lambda_p/fixed.h>
#include <lambda_p/tee.h>
#include <lambda_p/explode.h>

lambda_p::entry::entry (boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: next (new lambda_p::tee),
	errors (errors_a)
{
}

void lambda_p::entry::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments)
{
	for (auto i (fixed.begin ()), j (fixed.end ()); i != j; ++i)
	{
		(*(*i)) ();
	}
	auto explode (boost::shared_ptr <lambda_p::node> (new lambda_p::explode (arguments, errors)));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments_l;
	arguments_l.push_back (explode);
	(*next) (arguments_l);
}