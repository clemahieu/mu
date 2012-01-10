#include "builder.h"

#include <lambda_p_script_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script/operations/identity.h>

#include <boost/bind.hpp>

void lambda_p_script_io_test::builder::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_script_io_test::builder::run_1 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 1);
}

void lambda_p_script_io_test::builder::run_2 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	auto routine (builder.routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	auto n1 (boost::shared_ptr <lambda_p_script::operations::identity> (new lambda_p_script::operations::identity));
	arguments.push_back (n1);
	auto n2 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (n2);
	(*routine) (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == n2);
}