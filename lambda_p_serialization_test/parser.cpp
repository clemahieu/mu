#include "parser.h"

#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p_serialization_test/parser_result.h>
#include <lambda_p_serialization/tokens/stream_end.h>
#include <lambda_p_serialization/tokens/divider.h>
#include <lambda_p_serialization/tokens/identifier.h>
#include <lambda_p_serialization/tokens/left_square.h>
#include <lambda_p_serialization/tokens/right_square.h>
#include <lambda_p_serialization/ast/expression.h>
#include <lambda_p_serialization/ast/identifier.h>

#include <boost/bind.hpp>

void lambda_p_serialization_test::parser::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_serialization_test::parser::run_1 ()
{
	lambda_p_serialization_test::parser_result result;
	lambda_p_serialization::parser::parser parser (boost::bind (&lambda_p_serialization_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_serialization::tokens::stream_end);
	assert (result.results.empty ());
	assert (parser.error ().get () == nullptr);
}

void lambda_p_serialization_test::parser::run_2 ()
{
	lambda_p_serialization_test::parser_result result;
	lambda_p_serialization::parser::parser parser (boost::bind (&lambda_p_serialization_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_serialization::tokens::left_square);
	parser (new lambda_p_serialization::tokens::right_square);
	assert (result.results.size () == 1);
	auto n1 (result.results [0]);
	auto e1 (boost::dynamic_pointer_cast <lambda_p_serialization::ast::expression> (n1));
	assert (e1.get () != nullptr);
	assert (e1->values.empty ());
	assert (e1->full_name.empty ());
	assert (e1->individual_names.empty ());
}

void lambda_p_serialization_test::parser::run_3 ()
{
	lambda_p_serialization_test::parser_result result;
	lambda_p_serialization::parser::parser parser (boost::bind (&lambda_p_serialization_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_serialization::tokens::left_square);
	parser (new lambda_p_serialization::tokens::identifier (std::wstring (L"t1")));
	parser (new lambda_p_serialization::tokens::right_square);
	auto e1 (boost::dynamic_pointer_cast <lambda_p_serialization::ast::expression> (result.results [0]));
	assert (e1->values.size () == 1);
	auto i1 (boost::dynamic_pointer_cast <lambda_p_serialization::ast::identifier> (e1->values [0]));
	assert (i1->string == std::wstring (L"t1"));
	assert (e1->full_name.empty ());
	assert (e1->individual_names.empty ());
}