#include "simple_compile_test_1.h"

#include <lambda_p/lexer/lexer.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/parser/routine_vector.h>

#include <boost/bind.hpp>

lambda_p_test::simple_compile_test_1::simple_compile_test_1(void)
{
}

lambda_p_test::simple_compile_test_1::~simple_compile_test_1(void)
{
}

void lambda_p_test::simple_compile_test_1::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_test::simple_compile_test_1::run_1 ()
{
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::lexer::lexer lexer (boost::bind <void> (parser, _1));
}

void lambda_p_test::simple_compile_test_1::run_2 ()
{
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::lexer::lexer lexer (boost::bind <void> (parser, _1));
	std::wstring routine1 (L"routine1 ;; ;. ");
	std::wstring routine2 (L"routine2 ;; ;. ");
	for (std::wstring::const_iterator i = routine1.begin (); i != routine1.end (); ++i)
	{
		lexer (*i);
	}
	for (std::wstring::const_iterator i = routine2.begin (); i != routine2.end (); ++i)
	{
		lexer (*i);
	}
	assert (!parser.error ());
	assert (!lexer.error ());
}