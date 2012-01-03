#include "scatter.h"

#include <lambda_p/core/scatter.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/core/expression.h>

#include <boost/bind.hpp>

void lambda_p_test::scatter::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
}

void lambda_p_test::scatter::run_1 ()
{
	lambda_p::errors::error_list errors;
	lambda_p::core::scatter scatter (boost::bind (&lambda_p::errors::error_list::operator(), &errors, _1));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	scatter (arguments);
	assert (errors.errors.empty ());
}

void lambda_p_test::scatter::run_2 ()
{
	lambda_p::errors::error_list errors;
	lambda_p::core::scatter scatter (boost::bind (&lambda_p::errors::error_list::operator(), &errors, _1));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	scatter.set_required (0);
	scatter (arguments);
	assert (errors.errors.empty ());
}

void lambda_p_test::scatter::run_3 ()
{
	lambda_p::errors::error_list errors;
	lambda_p::core::scatter scatter (boost::bind (&lambda_p::errors::error_list::operator(), &errors, _1));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	scatter.set_required (1);
	scatter (arguments);
	assert (!errors.errors.empty ());
}

void lambda_p_test::scatter::run_4 ()
{
	lambda_p::errors::error_list errors;
	lambda_p::core::scatter scatter (boost::bind (&lambda_p::errors::error_list::operator(), &errors, _1));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	arguments.push_back (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	scatter.set_required (0);
	scatter (arguments);
	assert (!errors.errors.empty ());
}

void lambda_p_test::scatter::run_5 ()
{
	lambda_p::errors::error_list errors;
	lambda_p::core::scatter scatter (boost::bind (&lambda_p::errors::error_list::operator(), &errors, _1));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	arguments.push_back (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	scatter (arguments);
	assert (errors.errors.empty ());
}