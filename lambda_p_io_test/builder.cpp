#include "builder.h"

#include <lambda_p_io/source.h>
#include <lambda_p_io/builder.h>

#include <boost/bind.hpp>

void lambda_p_io_test::builder::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_io_test::builder::run_1 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 1);
}

void lambda_p_io_test::builder::run_2 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	source (L"[:~]");
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 2);
}