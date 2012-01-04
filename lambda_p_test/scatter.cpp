#include "scatter.h"

#include <lambda_p/scatter.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/node.h>

void lambda_p_test::scatter::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_test::scatter::run_1 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p::scatter scatter (0, errors);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	scatter (arguments);
	assert (errors->errors.empty ());
}

void lambda_p_test::scatter::run_2 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p::scatter scatter (0, errors);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	scatter (arguments);
	assert (errors->errors.empty ());
}

void lambda_p_test::scatter::run_3 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p::scatter scatter (1, errors);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	scatter (arguments);
	assert (!errors->errors.empty ());
}

void lambda_p_test::scatter::run_4 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_list> (new lambda_p::errors::error_list));
	lambda_p::scatter scatter (0, errors);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	arguments.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	scatter (arguments);
	assert (!errors->errors.empty ());
}