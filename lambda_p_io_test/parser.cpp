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
#include <lambda_p_io/ast/end.h>
#include <core/errors/error_list.h>

#include <boost/bind.hpp>

void lambda_p_io_test::parser::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
}

void lambda_p_io_test::parser::run_1 ()
{
	lambda_p_io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	lambda_p_io::parser::parser parser (errors, boost::bind (&lambda_p_io_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_io::tokens::stream_end, mu::core::context (0, 0, 0, 0, 0, 0));
	assert (result.results.size () == 1);
	auto end (boost::dynamic_pointer_cast <lambda_p_io::ast::end> (result.results [0]));
	assert (errors->errors.empty ());
}

void lambda_p_io_test::parser::run_2 ()
{
	lambda_p_io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	lambda_p_io::parser::parser parser (errors, boost::bind (&lambda_p_io_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_io::tokens::left_square, mu::core::context (1, 1, 0, 1, 1, 0));
	parser (new lambda_p_io::tokens::right_square, mu::core::context (1, 2, 1, 1, 2, 1));
	assert (result.results.size () == 1);
	auto n1 (result.results [0]);
	auto e1 (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (n1));
	assert (e1.get () != nullptr);
	assert (e1->values.empty ());
	assert (e1->full_name->string.empty ());
	assert (e1->individual_names.empty ());
	assert (e1->context == mu::core::context (1, 1, 0, 1, 2, 1));	
}

void lambda_p_io_test::parser::run_3 ()
{
	lambda_p_io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	lambda_p_io::parser::parser parser (errors, boost::bind (&lambda_p_io_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_io::tokens::left_square, mu::core::context (1, 1, 0, 1, 1, 0));
	parser (new lambda_p_io::tokens::identifier (std::wstring (L"t1")), mu::core::context (1, 2, 1, 1, 3, 2));
	parser (new lambda_p_io::tokens::right_square, mu::core::context (1, 4, 3, 1, 4, 3));
	auto e1 (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (result.results [0]));
	assert (e1->context == mu::core::context (1, 1, 0, 1, 4, 3));
	assert (e1->values.size () == 1);
	auto i1 (boost::dynamic_pointer_cast <lambda_p_io::ast::identifier> (e1->values [0]));
	assert (i1->string == std::wstring (L"t1"));
	assert (i1->context == mu::core::context (1, 2, 1, 1, 3, 2));
	assert (e1->full_name->string.empty ());
	assert (e1->individual_names.empty ());
}

void lambda_p_io_test::parser::run_4 ()
{
	lambda_p_io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	lambda_p_io::parser::parser parser (errors, boost::bind (&lambda_p_io_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_io::tokens::left_square, mu::core::context (1, 1, 0, 1, 1, 0));
	parser (new lambda_p_io::tokens::divider, mu::core::context (1, 2, 1, 1, 2, 1));
	parser (new lambda_p_io::tokens::identifier (std::wstring (L"t1")), mu::core::context (1, 3, 2, 1, 4, 3));
	parser (new lambda_p_io::tokens::right_square, mu::core::context (1, 5, 4, 1, 5, 4));
	auto e1 (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (result.results [0]));
	assert (e1->values.empty ());
	assert (e1->individual_names.size () == 1);
	assert (e1->context == mu::core::context (1, 1, 0, 1, 5, 4));
	auto i1 (e1->individual_names [0]);
	assert (i1->string == std::wstring (L"t1"));
	assert (e1->full_name->string.empty ());
}

void lambda_p_io_test::parser::run_5 ()
{
	lambda_p_io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	lambda_p_io::parser::parser parser (errors, boost::bind (&lambda_p_io_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_io::tokens::left_square, mu::core::context (1, 1, 0, 1, 1, 0));
	parser (new lambda_p_io::tokens::divider, mu::core::context (1, 2, 1, 1, 2, 1));
	parser (new lambda_p_io::tokens::divider, mu::core::context (1, 3, 2, 1, 3, 2));
	parser (new lambda_p_io::tokens::identifier (std::wstring (L"t1")), mu::core::context (1, 4, 3, 1, 5, 4));
	parser (new lambda_p_io::tokens::right_square, mu::core::context (1, 6, 5, 1, 6, 5));
	auto e1 (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (result.results [0]));
	assert (e1->values.empty ());
	assert (e1->individual_names.empty ());
	assert (e1->full_name->string == std::wstring (L"t1"));
	assert (e1->context == mu::core::context (1, 1, 0, 1, 6, 5));
}

void lambda_p_io_test::parser::run_6 ()
{
	lambda_p_io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	lambda_p_io::parser::parser parser (errors, boost::bind (&lambda_p_io_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_io::tokens::left_square, mu::core::context (1, 1, 0, 1, 1, 0));
	parser (new lambda_p_io::tokens::left_square, mu::core::context (1, 2, 1, 1, 2, 1));
	parser (new lambda_p_io::tokens::right_square, mu::core::context (1, 3, 2, 1, 3, 2));
	parser (new lambda_p_io::tokens::right_square, mu::core::context (1, 4, 3, 1, 4, 3));
	auto e1 (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (result.results [0]));
	assert (e1->values.size () == 1);
	assert (e1->individual_names.empty ());
	assert (e1->full_name->string.empty ());
	assert (e1->context == mu::core::context (1, 1, 0, 1, 4, 3));
	auto e2 (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (e1->values [0]));
	assert (e2->values.empty ());
	assert (e2->individual_names.empty ());
	assert (e2->full_name->string.empty ());
	assert (e2->context == mu::core::context (1, 2, 1, 1, 3, 2));
}

void lambda_p_io_test::parser::run_7 ()
{
	lambda_p_io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	lambda_p_io::parser::parser parser (errors, boost::bind (&lambda_p_io_test::parser_result::operator(), &result, _1));
	parser (new lambda_p_io::tokens::stream_end, mu::core::context (1, 1, 0, 1, 1, 0));
	assert (errors->errors.empty ());
	assert (result.results.size () == 1);
	auto end (boost::dynamic_pointer_cast <lambda_p_io::ast::end> (result.results [0]));
}