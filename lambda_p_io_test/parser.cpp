#include "parser.h"

#include <lambda_p_io/parser/parser.h>
#include <lambda_p_io_test/parser_result.h>
#include <lambda_p_io/tokens/stream_end.h>
#include <lambda_p_io/tokens/divider.h>
#include <lambda_p_io/tokens/identifier.h>
#include <lambda_p_io/tokens/left_square.h>
#include <lambda_p_io/tokens/right_square.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/identifier.h>

#include <boost/bind.hpp>

void lambda_p_io_test::parser::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
}

void lambda_p_io_test::parser::run_1 ()
{
	lambda_p_io_test::parser_result result;
	lambda_p_io::parser::parser parser (boost::bind (&lambda_p_io_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_io::tokens::stream_end);
	assert (result.results.empty ());
	assert (parser.error ().get () == nullptr);
}

void lambda_p_io_test::parser::run_2 ()
{
	lambda_p_io_test::parser_result result;
	lambda_p_io::parser::parser parser (boost::bind (&lambda_p_io_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_io::tokens::left_square);
	parser (new lambda_p_io::tokens::right_square);
	assert (result.results.size () == 1);
	auto n1 (result.results [0]);
	auto e1 (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (n1));
	assert (e1.get () != nullptr);
	assert (e1->values.empty ());
	assert (e1->full_name.empty ());
	assert (e1->individual_names.empty ());
}

void lambda_p_io_test::parser::run_3 ()
{
	lambda_p_io_test::parser_result result;
	lambda_p_io::parser::parser parser (boost::bind (&lambda_p_io_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_io::tokens::left_square);
	parser (new lambda_p_io::tokens::identifier (std::wstring (L"t1")));
	parser (new lambda_p_io::tokens::right_square);
	auto e1 (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (result.results [0]));
	assert (e1->values.size () == 1);
	auto i1 (boost::dynamic_pointer_cast <lambda_p_io::ast::identifier> (e1->values [0]));
	assert (i1->string == std::wstring (L"t1"));
	assert (e1->full_name.empty ());
	assert (e1->individual_names.empty ());
}

void lambda_p_io_test::parser::run_4 ()
{
	lambda_p_io_test::parser_result result;
	lambda_p_io::parser::parser parser (boost::bind (&lambda_p_io_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_io::tokens::left_square);
	parser (new lambda_p_io::tokens::divider);
	parser (new lambda_p_io::tokens::identifier (std::wstring (L"t1")));
	parser (new lambda_p_io::tokens::right_square);
	auto e1 (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (result.results [0]));
	assert (e1->values.empty ());
	assert (e1->individual_names.size () == 1);
	auto i1 (e1->individual_names [0]);
	assert (i1 == std::wstring (L"t1"));
	assert (e1->full_name.empty ());
}

void lambda_p_io_test::parser::run_5 ()
{
	lambda_p_io_test::parser_result result;
	lambda_p_io::parser::parser parser (boost::bind (&lambda_p_io_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_io::tokens::left_square);
	parser (new lambda_p_io::tokens::divider);
	parser (new lambda_p_io::tokens::divider);
	parser (new lambda_p_io::tokens::identifier (std::wstring (L"t1")));
	parser (new lambda_p_io::tokens::right_square);
	auto e1 (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (result.results [0]));
	assert (e1->values.empty ());
	assert (e1->individual_names.empty ());
	assert (e1->full_name == std::wstring (L"t1"));
}

void lambda_p_io_test::parser::run_6 ()
{
	lambda_p_io_test::parser_result result;
	lambda_p_io::parser::parser parser (boost::bind (&lambda_p_io_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_io::tokens::left_square);
	parser (new lambda_p_io::tokens::left_square);
	parser (new lambda_p_io::tokens::right_square);
	parser (new lambda_p_io::tokens::right_square);
	auto e1 (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (result.results [0]));
	assert (e1->values.size () == 1);
	assert (e1->individual_names.empty ());
	assert (e1->full_name.empty ());
	auto e2 (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (e1->values [0]));
	assert (e2->values.empty ());
	assert (e2->individual_names.empty ());
	assert (e2->full_name.empty ());
}