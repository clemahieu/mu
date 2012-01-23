#include "lambda.h"

#include <lambda_p_script_io/builder.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script/integer/node.h>

#include <boost/bind.hpp>

void lambda_p_script_io_test::lambda::run ()
{
	//run_1 ();
}

void lambda_p_script_io_test::lambda::run_1 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=>[.id # d42]]");
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 1);
	auto routine (builder.routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine->perform (builder.errors, arguments, results);
	assert (builder.errors->errors.empty ());
	assert (results.size () == 1);
	auto number (boost::dynamic_pointer_cast <lambda_p_script::integer::node> (results [0]));
	assert (number.get () != nullptr);
	assert (number->value == 42);
}