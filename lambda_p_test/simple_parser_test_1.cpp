#include "simple_parser_test_1.h"

#include <lambda_p/parser/simple_parser.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/parser/parse_result.h>
#include <lambda_p/parser/routine_vector.h>
#include <lambda_p/lexer/token_vector.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/tokens/statement_end.h>
#include <lambda_p/tokens/routine_end.h>
#include <lambda_p/tokens/complex_identifier.h>
#include <lambda_p/tokens/declaration.h>
#include <lambda_p/tokens/data_token.h>

#include <vector>
#include <sstream>

lambda_p_test::simple_parser_test_1::simple_parser_test_1(void)
{
}

lambda_p_test::simple_parser_test_1::~simple_parser_test_1(void)
{
}

void lambda_p_test::simple_parser_test_1::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
	run_8 ();
	run_9 ();
	run_10 ();
}

void lambda_p_test::simple_parser_test_1::run_1 ()
{
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::parser::routine_vector routines;
	::lambda_p::parser::simple_parser parser (routines);
	assert (!parser.error ());
}

void lambda_p_test::simple_parser_test_1::run_2 ()
{
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::parser::routine_vector routines;
	::lambda_p::parser::simple_parser parser (routines);
	::lambda_p::tokens::identifier identifier (::std::wstring (L"routine"));
	::lambda_p::tokens::statement_end statement_end;
	::lambda_p::tokens::routine_end routine_end;
	parser (&identifier);
	parser (&statement_end);
	parser (&routine_end);
	assert (!parser.error ());
	assert (parser.current_state () == ::lambda_p::parser::state_begin);
	::std::vector < ::lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::simple_parser_test_1::run_3 ()
{
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::parser::routine_vector routines;
	::lambda_p::parser::simple_parser parser (routines);
	::lambda_p::tokens::identifier identifier (::std::wstring (L"routine"));
	::lambda_p::tokens::declaration decl;
	::lambda_p::tokens::identifier parameter1 (::std::wstring (L"parameter1"));
	::lambda_p::tokens::statement_end statement_end;
	::lambda_p::tokens::routine_end routine_end;
	parser (&identifier);
	parser (&decl);
	parser (&parameter1);
	parser (&statement_end);
	parser (&routine_end);
	assert (!parser.error ());
	assert (parser.current_state () == ::lambda_p::parser::state_begin);
	::std::vector < ::lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::simple_parser_test_1::run_4 ()
{
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::parser::routine_vector routines;
	::lambda_p::parser::simple_parser parser (routines);
	::lambda_p::tokens::identifier identifier (::std::wstring (L"routine"));
	::lambda_p::tokens::declaration decl;
	::lambda_p::tokens::identifier parameter1 (::std::wstring (L"parameter1"));
	::lambda_p::tokens::statement_end se1;
	::lambda_p::tokens::identifier s1 (::std::wstring (L"statement1"));
	::lambda_p::tokens::identifier targets1 (::std::wstring (L"routine"));
	::lambda_p::tokens::identifier targeta1 (::std::wstring (L"parameter1"));
	::lambda_p::tokens::statement_end se2;
	::lambda_p::tokens::routine_end routine_end;
	parser (&identifier);
	parser (&decl);
	parser (&parameter1);
	parser (&se1);
	parser (&s1);
	parser (&targets1);
	parser (&targeta1);
	parser (&se2);
	parser (&routine_end);
	assert (!parser.error ());
	assert (parser.current_state () == ::lambda_p::parser::state_begin);
	::std::vector < ::lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::simple_parser_test_1::run_5 ()
{
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::parser::routine_vector routines;
	::lambda_p::parser::simple_parser parser (routines);
	::lambda_p::tokens::identifier identifier (::std::wstring (L"routine"));
	::lambda_p::tokens::declaration decl;
	::lambda_p::tokens::identifier parameter1 (::std::wstring (L"parameter1"));
	::lambda_p::tokens::statement_end se1;
	::lambda_p::tokens::identifier s1 (::std::wstring (L"statement1"));
	::lambda_p::tokens::identifier targets1 (::std::wstring (L"routine"));
	::lambda_p::tokens::identifier targeta1 (::std::wstring (L"parameter1"));
	::lambda_p::tokens::declaration decs1;
	::lambda_p::tokens::identifier deca1 (::std::wstring (L"declaration2"));
	::lambda_p::tokens::statement_end se2;
	::lambda_p::tokens::routine_end routine_end;
	parser (&identifier);
	parser (&decl);
	parser (&parameter1);
	parser (&se1);
	parser (&s1);
	parser (&targets1);
	parser (&targeta1);
	parser (&decs1);
	parser (&deca1);
	parser (&se2);
	parser (&routine_end);
	assert (!parser.error ());
	assert (parser.current_state () == ::lambda_p::parser::state_begin);
	::std::vector < ::lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::simple_parser_test_1::run_6 ()
{
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::parser::routine_vector routines;
	::lambda_p::parser::simple_parser parser (routines);
	::lambda_p::tokens::identifier identifier (::std::wstring (L"routine"));
	::lambda_p::tokens::declaration decl;
	::lambda_p::tokens::identifier parameter1 (::std::wstring (L"parameter1"));
	::lambda_p::tokens::statement_end se1;
	::lambda_p::tokens::identifier s1 (::std::wstring (L"statement1"));
	::lambda_p::tokens::identifier targets1 (::std::wstring (L"routine"));
	::lambda_p::tokens::identifier targeta1 (::std::wstring (L"parameter1"));
	::lambda_p::tokens::declaration decs1;
	::lambda_p::tokens::identifier deca1 (::std::wstring (L"declaration2"));
	::lambda_p::tokens::statement_end se2;
	::lambda_p::tokens::identifier s2 (::std::wstring (L"statement2"));
	::lambda_p::tokens::identifier targets2 (::std::wstring (L"statement1"));
	::lambda_p::tokens::identifier targeta2 (::std::wstring (L"declaration2"));
	::lambda_p::tokens::statement_end se3;
	::lambda_p::tokens::routine_end routine_end;
	parser (&identifier);
	parser (&decl);
	parser (&parameter1);
	parser (&se1);
	parser (&s1);
	parser (&targets1);
	parser (&targeta1);
	parser (&decs1);
	parser (&deca1);
	parser (&se2);
	parser (&s2);
	parser (&targets2);
	parser (&targeta2);
	parser (&se3);
	parser (&routine_end);
	assert (!parser.error ());
	assert (parser.current_state () == ::lambda_p::parser::state_begin);
	::std::vector < ::lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::simple_parser_test_1::run_7 ()
{
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::parser::routine_vector routines;
	::lambda_p::parser::simple_parser parser (routines);
	::lambda_p::tokens::complex_identifier identifier (::std::wstring (L"routine \0\t\n\fhello"), ::std::wstring (L"abcdef"));
	::lambda_p::tokens::declaration decl;
	::lambda_p::tokens::complex_identifier parameter1 (::std::wstring (L"parameter1 \0\t\n\fhello"), ::std::wstring (L"abcdef"));
	::lambda_p::tokens::statement_end se1;
	::lambda_p::tokens::complex_identifier s1 (::std::wstring (L"statement1 \0\t\n\fhello"), ::std::wstring (L"abcdef"));
	::lambda_p::tokens::complex_identifier targets1 (::std::wstring (L"routine \0\t\n\fhello"), ::std::wstring (L"abcdef"));
	::lambda_p::tokens::complex_identifier targeta1 (::std::wstring (L"parameter1 \0\t\n\fhello"), ::std::wstring (L"abcdef"));
	::lambda_p::tokens::declaration decs1;
	::lambda_p::tokens::complex_identifier deca1 (::std::wstring (L"declaration2 \0\t\n\fhello"), ::std::wstring (L"abcdef"));
	::lambda_p::tokens::statement_end se2;
	::lambda_p::tokens::complex_identifier s2 (::std::wstring (L"statement2 \0\t\n\fhello"), ::std::wstring (L"abcdef"));
	::lambda_p::tokens::complex_identifier targets2 (::std::wstring (L"statement1 \0\t\n\fhello"), ::std::wstring (L"abcdef"));
	::lambda_p::tokens::complex_identifier targeta2 (::std::wstring (L"declaration2 \0\t\n\fhello"), ::std::wstring (L"abcdef"));
	::lambda_p::tokens::statement_end se3;
	::lambda_p::tokens::routine_end routine_end;
	parser (&identifier);
	parser (&decl);
	parser (&parameter1);
	parser (&se1);
	parser (&s1);
	parser (&targets1);
	parser (&targeta1);
	parser (&decs1);
	parser (&deca1);
	parser (&se2);
	parser (&s2);
	parser (&targets2);
	parser (&targeta2);
	parser (&se3);
	parser (&routine_end);
	assert (!parser.error ());
	assert (parser.current_state () == ::lambda_p::parser::state_begin);
	::std::vector < ::lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::simple_parser_test_1::run_8 ()
{
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::parser::routine_vector routines;
	::lambda_p::parser::simple_parser parser (routines);
	::lambda_p::tokens::identifier identifier (::std::wstring (L"routine"));
	::lambda_p::tokens::declaration decl;
	::lambda_p::tokens::identifier parameter1 (::std::wstring (L"parameter1"));
	::lambda_p::tokens::statement_end se1;
	::lambda_p::tokens::identifier s1 (::std::wstring (L"statement1"));
	::lambda_p::tokens::identifier targets1 (::std::wstring (L"routine"));
	::lambda_p::tokens::identifier targeta1 (::std::wstring (L"parameter1"));
	::lambda_p::tokens::data_token dt1;
	::lambda_p::tokens::complex_identifier d1 (::std::wstring (L"manifest data \0\t\n\f and more \u0983 \u23098"), ::std::wstring (L"abcdef"));
	::lambda_p::tokens::statement_end se2;
	::lambda_p::tokens::routine_end routine_end;
	parser (&identifier);
	parser (&decl);
	parser (&parameter1);
	parser (&se1);
	parser (&s1);
	parser (&targets1);
	parser (&targeta1);
	parser (&dt1);
	parser (&d1);
	parser (&se2);
	parser (&routine_end);
	assert (!parser.error ());
	assert (parser.current_state () == ::lambda_p::parser::state_begin);
	::std::vector < ::lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::simple_parser_test_1::run_9 ()
{
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::parser::routine_vector routines;
	::lambda_p::parser::simple_parser parser (routines);
	::lambda_p::tokens::identifier identifier (::std::wstring (L"routine"));
	::lambda_p::tokens::declaration decl;
	::lambda_p::tokens::identifier parameter1 (::std::wstring (L"parameter1"));
	::lambda_p::tokens::statement_end se1;
	::lambda_p::tokens::identifier s1 (::std::wstring (L"statement1"));
	::lambda_p::tokens::identifier targets1 (::std::wstring (L"routine"));
	::lambda_p::tokens::identifier targeta1 (::std::wstring (L"parameter1"));
	::lambda_p::tokens::data_token dt1;
	::lambda_p::tokens::identifier d1 (::std::wstring (L"161871606870670184030848abcef654066450"));
	::lambda_p::tokens::statement_end se2;
	::lambda_p::tokens::routine_end routine_end;
	parser (&identifier);
	parser (&decl);
	parser (&parameter1);
	parser (&se1);
	parser (&s1);
	parser (&targets1);
	parser (&targeta1);
	parser (&dt1);
	parser (&d1);
	parser (&se2);
	parser (&routine_end);
	assert (!parser.error ());
	assert (parser.current_state () == ::lambda_p::parser::state_begin);
	::std::vector < ::lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}


void lambda_p_test::simple_parser_test_1::run_10 ()
{
	::lambda_p::lexer::token_vector tokens;
	::lambda_p::parser::routine_vector routines;
	::lambda_p::parser::simple_parser parser (routines);
	::lambda_p::tokens::routine_end routine_end;
	parser (&routine_end);
	assert (!parser.error ());
	assert (parser.current_state () == ::lambda_p::parser::state_begin);
	::std::vector < ::lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}
