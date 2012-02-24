#include "extension.h"

#include <lambda_p_script_io/builder.h>
#include <io/source.h>

#include <boost/bind.hpp>

void lambda_p_script_test::string::extension::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_script_test::string::extension::run_1 ()
{
	lambda_p_script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[` ;; 1]");
	assert (!builder.errors->errors.empty ());
	auto e1 (builder.errors->errors [0]);
	assert (e1.second == mu::core::context (1, 2, 1, 1, 2, 1));
}

void lambda_p_script_test::string::extension::run_2 ()
{
	lambda_p_script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[`[] ;; 1]");
	assert (!builder.errors->errors.empty ());
	auto e1 (builder.errors->errors [0]);
	assert (e1.second == mu::core::context (1, 2, 1, 1, 4, 3));
}

void lambda_p_script_test::string::extension::run_3 ()
{
	lambda_p_script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[` a ;; 1]");
	assert (builder.errors->errors.empty ());
}