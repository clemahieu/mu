#include "lambda.h"

#include <lambda_p_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p/routine.h>
#include <lambda_p/expression.h>

#include <boost/bind.hpp>

void lambda_p_io_test::lambda::run ()
{
	run_1 ();
}

void lambda_p_io_test::lambda::run_1 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=>[]]");
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 1);
	auto routine (builder.routines [0]);
	assert (routine->body->dependencies.size () == 1);
	auto lambda (boost::dynamic_pointer_cast <lambda_p::routine> (routine->body->dependencies [0]));
	assert (lambda.get () != nullptr);
}