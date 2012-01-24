#include "extension.h"

#include <lambda_p_script_io/builder.h>
#include <lambda_p_io/source.h>

#include <boost/bind.hpp>

void lambda_p_script_test::string::extension::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_script_test::string::extension::run_1 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[`]");
	assert (!builder.errors->errors.empty ());
	auto e1 (builder.errors->errors [0]);
	assert (e1.second == lambda_p::context (1, 2, 1, 1, 2, 1));
}

void lambda_p_script_test::string::extension::run_2 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[`[]]");
	assert (!builder.errors->errors.empty ());
	auto e1 (builder.errors->errors [0]);
	assert (e1.second == lambda_p::context (1, 2, 1, 1, 4, 3));
}