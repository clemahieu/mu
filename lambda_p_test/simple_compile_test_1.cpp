#include "simple_compile_test_1.h"

#include <lambda_p/serialization/lexer/simple_lexer.h>
#include <lambda_p/serialization/parser/simple_parser.h>

lambda_p_test::simple_compile_test_1::simple_compile_test_1(void)
{
}

lambda_p_test::simple_compile_test_1::~simple_compile_test_1(void)
{
}

struct routine_vector
{
	void operator () (::boost::shared_ptr < ::lambda_p::core::routine> result)
	{
		routines.push_back (result);
	}
	::std::vector < ::boost::shared_ptr < ::lambda_p::core::routine> > routines;
};

void lambda_p_test::simple_compile_test_1::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_test::simple_compile_test_1::run_1 ()
{
	routine_vector routines;
	::lambda_p::serialization::parser::simple_parser <routine_vector> parser (routines);
	::lambda_p::serialization::lexer::simple_lexer lexer (::boost::function <void (::lambda_p::tokens::token *)> (parser));
}

void lambda_p_test::simple_compile_test_1::run_2 ()
{
	routine_vector routines;
	::lambda_p::serialization::parser::simple_parser <routine_vector> parser (routines);
	::boost::function <void (::lambda_p::tokens::token *)> target (parser);
	::lambda_p::serialization::lexer::simple_lexer lexer (target);
	::std::wstring routine1 (L"routine1 ;; ;. ");
	::std::wstring routine2 (L"routine2 ;; ;. ");
	for (::std::wstring::const_iterator i = routine1.begin (); i != routine1.end (); ++i)
	{
		lexer (*i);
	}
	for (::std::wstring::const_iterator i = routine2.begin (); i != routine2.end (); ++i)
	{
		lexer (*i);
	}
	assert (!parser.error ());
	assert (!lexer.error ());
}