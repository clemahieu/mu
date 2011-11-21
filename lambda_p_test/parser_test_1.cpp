#include "parser_test_1.h"

#include <lambda_p/parser/parser.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/parser/routine_vector.h>
#include <lambda_p/lexer/token_vector.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/tokens/divider.h>
#include <lambda_p/tokens/routine_end.h>
#include <lambda_p/tokens/complex_identifier.h>
#include <lambda_p/tokens/data.h>
#include <lambda_p/tokens/stream_end.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/parser/finished.h>
#include <lambda_p/parser/begin.h>

#include <vector>
#include <sstream>

lambda_p_test::parser_test_1::parser_test_1(void)
{
}

lambda_p_test::parser_test_1::~parser_test_1(void)
{
}

void lambda_p_test::parser_test_1::run ()
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
	run_11 ();
	run_12 ();
	run_13 ();
	run_14 ();
	run_15 ();
}

void lambda_p_test::parser_test_1::run_1 ()
{
	::lambda_p::lexer::token_vector tokens;
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	assert (!parser.error ());
}

void lambda_p_test::parser_test_1::run_2 ()
{
	::lambda_p::lexer::token_vector tokens;
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::tokens::divider connector;
	lambda_p::tokens::divider statement_end;
	lambda_p::tokens::routine_end routine_end;
	parser (&connector);
	parser (&statement_end);
	parser (&routine_end);
	assert (!parser.error ());
	assert (boost::dynamic_pointer_cast <lambda_p::parser::begin> (parser.state.top ()).get () != nullptr);
	std::vector < lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::parser_test_1::run_3 ()
{
	::lambda_p::lexer::token_vector tokens;
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::tokens::identifier parameter1 (std::wstring (L"parameter1"));
    lambda_p::tokens::divider connector;
	lambda_p::tokens::divider statement_end;
	lambda_p::tokens::routine_end routine_end;
    parser (&connector);
	parser (&parameter1);
	parser (&statement_end);
	parser (&routine_end);
	assert (!parser.error ());
	assert (boost::dynamic_pointer_cast <lambda_p::parser::begin> (parser.state.top ()).get () != nullptr);
	std::vector < lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::parser_test_1::run_4 ()
{
	::lambda_p::lexer::token_vector tokens;
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::tokens::identifier parameter1 (std::wstring (L"parameter1"));
    lambda_p::tokens::divider connector;
	lambda_p::tokens::divider se1;
	lambda_p::tokens::identifier targeta1 (std::wstring (L"parameter1"));
    lambda_p::tokens::divider c2;
	lambda_p::tokens::divider se2;
	lambda_p::tokens::routine_end routine_end;
    parser (&connector);
	parser (&parameter1);
	parser (&se1);
	parser (&targeta1);
    parser (&c2);
	parser (&se2);
	parser (&routine_end);
	assert (!parser.error ());
	assert (boost::dynamic_pointer_cast <lambda_p::parser::begin> (parser.state.top ()).get () != nullptr);
	std::vector < lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::parser_test_1::run_5 ()
{
	::lambda_p::lexer::token_vector tokens;
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::tokens::identifier parameter1 (std::wstring (L"parameter1"));
    lambda_p::tokens::divider c1;
	lambda_p::tokens::divider se1;
	lambda_p::tokens::identifier targeta1 (std::wstring (L"parameter1"));
	lambda_p::tokens::identifier deca1 (std::wstring (L"declaration2"));
    lambda_p::tokens::divider c2;
	lambda_p::tokens::divider se2;
	lambda_p::tokens::routine_end routine_end;
    parser (&c1);
	parser (&parameter1);
	parser (&se1);
	parser (&targeta1);
	parser (&c2);
	parser (&deca1);
	parser (&se2);
	parser (&routine_end);
	assert (!parser.error ());
	assert (boost::dynamic_pointer_cast <lambda_p::parser::begin> (parser.state.top ()).get () != nullptr);
	std::vector < lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::parser_test_1::run_6 ()
{
	::lambda_p::lexer::token_vector tokens;
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::tokens::identifier parameter1 (std::wstring (L"parameter1"));
    lambda_p::tokens::divider c1;
	lambda_p::tokens::divider se1;
	lambda_p::tokens::identifier targeta1 (std::wstring (L"parameter1"));
	lambda_p::tokens::identifier deca1 (std::wstring (L"declaration2"));
    lambda_p::tokens::divider c2;
	lambda_p::tokens::divider se2;
	lambda_p::tokens::identifier targeta2 (std::wstring (L"declaration2"));
    lambda_p::tokens::divider c3;
	lambda_p::tokens::divider se3;
	lambda_p::tokens::routine_end routine_end;
    parser (&c1);
	parser (&parameter1);
	parser (&se1);
	parser (&targeta1);
    parser (&c2);
	parser (&deca1);
	parser (&se2);
	parser (&targeta2);
    parser (&c3);
	parser (&se3);
	parser (&routine_end);
	assert (!parser.error ());
	assert (boost::dynamic_pointer_cast <lambda_p::parser::begin> (parser.state.top ()).get () != nullptr);
	std::vector < lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::parser_test_1::run_7 ()
{
	::lambda_p::lexer::token_vector tokens;
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::tokens::complex_identifier parameter1 (std::wstring (L"parameter1 \0\t\n\fhello"), std::wstring (L"abcdef"));
    lambda_p::tokens::divider c1;
	lambda_p::tokens::divider se1;
	lambda_p::tokens::complex_identifier targeta1 (std::wstring (L"parameter1 \0\t\n\fhello"), std::wstring (L"abcdef"));
	lambda_p::tokens::complex_identifier deca1 (std::wstring (L"declaration2 \0\t\n\fhello"), std::wstring (L"abcdef"));
    lambda_p::tokens::divider c2;
	lambda_p::tokens::divider se2;
	lambda_p::tokens::complex_identifier targeta2 (std::wstring (L"declaration2 \0\t\n\fhello"), std::wstring (L"abcdef"));
    lambda_p::tokens::divider c3;
	lambda_p::tokens::divider se3;
	lambda_p::tokens::routine_end routine_end;
    parser (&c1);
	parser (&parameter1);
	parser (&se1);
	parser (&targeta1);
    parser (&c2);
	parser (&deca1);
	parser (&se2);
	parser (&targeta2);
    parser (&c3);
	parser (&se3);
	parser (&routine_end);
	assert (!parser.error ());
	assert (boost::dynamic_pointer_cast <lambda_p::parser::begin> (parser.state.top ()).get () != nullptr);
	std::vector < lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::parser_test_1::run_8 ()
{
	::lambda_p::lexer::token_vector tokens;
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::tokens::identifier parameter1 (std::wstring (L"parameter1"));
    lambda_p::tokens::divider c1;
	lambda_p::tokens::divider se1;
	lambda_p::tokens::identifier targeta1 (std::wstring (L"parameter1"));
    lambda_p::tokens::divider c2;
	lambda_p::tokens::data dt1;
	lambda_p::tokens::complex_identifier d1 (std::wstring (L"manifest data \0\t\n\f and more \u0983 \u23098"), std::wstring (L"abcdef"));
	lambda_p::tokens::divider se2;
	lambda_p::tokens::routine_end routine_end;
    parser (&c1);
	parser (&parameter1);
	parser (&se1);
	parser (&targeta1);
	parser (&dt1);
	parser (&d1);
    parser (&c2);
	parser (&se2);
	parser (&routine_end);
	assert (!parser.error ());
	assert (boost::dynamic_pointer_cast <lambda_p::parser::begin> (parser.state.top ()).get () != nullptr);
	std::vector < lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::parser_test_1::run_9 ()
{
	::lambda_p::lexer::token_vector tokens;
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::tokens::identifier parameter1 (std::wstring (L"parameter1"));
    lambda_p::tokens::divider c1;
	lambda_p::tokens::divider se1;
	lambda_p::tokens::identifier targeta1 (std::wstring (L"parameter1"));
    lambda_p::tokens::divider c2;
	lambda_p::tokens::data dt1;
	lambda_p::tokens::identifier d1 (std::wstring (L"161871606870670184030848abcef654066450"));
	lambda_p::tokens::divider se2;
	lambda_p::tokens::routine_end routine_end;
    parser (&c1);
	parser (&parameter1);
	parser (&se1);
	parser (&targeta1);
	parser (&dt1);
	parser (&d1);
    parser (&c2);
	parser (&se2);
	parser (&routine_end);
	assert (!parser.error ());
	assert (boost::dynamic_pointer_cast <lambda_p::parser::begin> (parser.state.top ()).get () != nullptr);
	std::vector < lambda_p::errors::error *> problems;
	assert (routines.routines->size () == 1);
	(*routines.routines) [0]->validate (problems);
	assert (problems.size () == 0);
}

void lambda_p_test::parser_test_1::run_10 ()
{
	::lambda_p::lexer::token_vector tokens;
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	::lambda_p::tokens::stream_end stream_end;
	parser (&stream_end);
	assert (!parser.error ());
	assert (boost::dynamic_pointer_cast <lambda_p::parser::finished> (parser.state.top ()).get () != nullptr);
	assert (routines.routines->size () == 0);
}

void lambda_p_test::parser_test_1::run_11 ()
{
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::tokens::divider t1;
	lambda_p::tokens::identifier t2 (std::wstring (L"1"));
	lambda_p::tokens::identifier t3 (std::wstring (L"2"));
	lambda_p::tokens::divider t4;
	lambda_p::tokens::identifier t5 (std::wstring (L"1"));
	lambda_p::tokens::identifier t6 (std::wstring (L"2"));
	lambda_p::tokens::divider t7;
	lambda_p::tokens::divider t8;
	lambda_p::tokens::routine_end t9;
	parser (&t1);
	parser (&t2);
	parser (&t3);
	parser (&t4);
	parser (&t5);
	parser (&t6);
	parser (&t7);
	parser (&t8);
	parser (&t9);
	assert (!parser.error ());
	std::vector < lambda_p::errors::error *> errors;
	(*routines.routines)[0]->validate (errors);
	assert (errors.size () == 0);
	assert (routines.routines->size () == 1);
	assert ((*routines.routines)[0]->statements.size () == 1);
	assert ((*routines.routines)[0]->statements [0]->association->references.size () == 1);
	assert ((*routines.routines)[0]->statements [0]->association->references [0] != 0);
}

void lambda_p_test::parser_test_1::run_12 ()
{
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::tokens::divider t1;
	lambda_p::tokens::identifier t2 (std::wstring (L"e"));
	lambda_p::tokens::divider t3;
	lambda_p::tokens::identifier t4 (std::wstring (L"e"));
	lambda_p::tokens::identifier t5 (std::wstring (L"c"));
	lambda_p::tokens::divider t6;
	lambda_p::tokens::divider t7;
	lambda_p::tokens::routine_end t8;
	parser (&t1);
	parser (&t2);
	parser (&t3);
	parser (&t4);
	parser (&t5);
	parser (&t6);
	parser (&t7);
	parser (&t8);
	assert (parser.error ());
}

void lambda_p_test::parser_test_1::run_13 ()
{
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::tokens::identifier t1 (std::wstring (L"c"));
	lambda_p::tokens::divider t2;
	lambda_p::tokens::identifier t3 (std::wstring (L"e"));
	lambda_p::tokens::divider t4;
	lambda_p::tokens::identifier t5 (std::wstring (L"e"));
	lambda_p::tokens::divider t6;
	lambda_p::tokens::identifier t7 (std::wstring (L"c"));
	lambda_p::tokens::divider t8;
	lambda_p::tokens::routine_end t9;
	parser (&t1);
	parser (&t2);
	parser (&t3);
	parser (&t4);
	parser (&t5);
	parser (&t6);
	parser (&t7);
	parser (&t8);
	parser (&t9);
	assert (!parser.error ());
}

void lambda_p_test::parser_test_1::run_14 ()
{
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::tokens::identifier t1 (std::wstring (L"c"));
	lambda_p::tokens::identifier t2 (std::wstring (L"d1"));
	lambda_p::tokens::identifier t3 (std::wstring (L"d2"));
	lambda_p::tokens::identifier t4 (std::wstring (L"d3"));
	lambda_p::tokens::identifier t5 (std::wstring (L"d4"));
	lambda_p::tokens::divider t6;
	lambda_p::tokens::identifier t7 (std::wstring (L"e"));
	lambda_p::tokens::divider t8;
	lambda_p::tokens::identifier t9 (std::wstring (L"e"));
	lambda_p::tokens::divider t10;
	lambda_p::tokens::identifier t11 (std::wstring (L"c"));
	lambda_p::tokens::identifier t12 (std::wstring (L"d1"));
	lambda_p::tokens::identifier t13 (std::wstring (L"d2"));
	lambda_p::tokens::identifier t14 (std::wstring (L"d3"));
	lambda_p::tokens::identifier t15 (std::wstring (L"d4"));
	lambda_p::tokens::divider t16;
	lambda_p::tokens::routine_end t17;
	parser (&t1);
	parser (&t2);
	parser (&t3);
	parser (&t4);
	parser (&t5);
	parser (&t6);
	parser (&t7);
	parser (&t8);
	parser (&t9);
	parser (&t10);
	parser (&t11);
	parser (&t12);
	parser (&t13);
	parser (&t14);
	parser (&t15);
	parser (&t16);
	parser (&t17);
	assert (!parser.error ());
}

// Test direct linking surface declarations to references
void lambda_p_test::parser_test_1::run_15 ()
{
	lambda_p::parser::routine_vector routines;
	lambda_p::parser::parser parser (routines);
	lambda_p::tokens::identifier t1 (std::wstring (L"c"));
	lambda_p::tokens::divider t2;
	lambda_p::tokens::identifier t3 (std::wstring (L"c"));
	lambda_p::tokens::divider t4;
	lambda_p::tokens::routine_end t5;
	parser (&t1);
	parser (&t2);
	parser (&t3);
	parser (&t4);
	parser (&t5);
	assert (!parser.error ());
}