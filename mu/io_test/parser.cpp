#include "parser.h"

#include <mu/io/parser.parser.h>
#include <mu/io_test/parser_result.h>
#include <mu/io/tokens.stream_end.h>
#include <mu/io/tokens.divider.h>
#include <mu/io/tokens.identifier.h>
#include <mu/io/tokens.left_square.h>
#include <mu/io/tokens.right_square.h>
#include <mu/io/ast.expression.h>
#include <mu/io/ast.identifier.h>
#include <mu/io/ast.end.h>
#include <mu/core/errors.error_list.h>

#include <boost/bind.hpp>

void mu::io_test::parser::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
}

void mu::io_test::parser::run_1 ()
{
	mu::io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::parser::parser parser (errors, boost::bind (&mu::io_test::parser_result::operator(), &result, _1));
	parser (new mu::io::tokens::stream_end, mu::core::context (0, 0, 0, 0, 0, 0));
	assert (result.results.size () == 1);
	auto end (boost::dynamic_pointer_cast <mu::io::ast::end> (result.results [0]));
	assert (errors->errors.empty ());
}

void mu::io_test::parser::run_2 ()
{
	mu::io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::parser::parser parser (errors, boost::bind (&mu::io_test::parser_result::operator(), &result, _1));
	parser (new mu::io::tokens::left_square, mu::core::context (1, 1, 0, 1, 1, 0));
	parser (new mu::io::tokens::right_square, mu::core::context (1, 2, 1, 1, 2, 1));
	assert (result.results.size () == 1);
	auto n1 (result.results [0]);
	auto e1 (boost::dynamic_pointer_cast <mu::io::ast::expression> (n1));
	assert (e1.get () != nullptr);
	assert (e1->values.empty ());
	assert (e1->full_name->string.empty ());
	assert (e1->individual_names.empty ());
	assert (e1->context == mu::core::context (1, 1, 0, 1, 2, 1));	
}

void mu::io_test::parser::run_3 ()
{
	mu::io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::parser::parser parser (errors, boost::bind (&mu::io_test::parser_result::operator(), &result, _1));
	parser (new mu::io::tokens::left_square, mu::core::context (1, 1, 0, 1, 1, 0));
	parser (new mu::io::tokens::identifier (std::wstring (L"t1")), mu::core::context (1, 2, 1, 1, 3, 2));
	parser (new mu::io::tokens::right_square, mu::core::context (1, 4, 3, 1, 4, 3));
	auto e1 (boost::dynamic_pointer_cast <mu::io::ast::expression> (result.results [0]));
	assert (e1->context == mu::core::context (1, 1, 0, 1, 4, 3));
	assert (e1->values.size () == 1);
	auto i1 (boost::dynamic_pointer_cast <mu::io::ast::identifier> (e1->values [0]));
	assert (i1->string == std::wstring (L"t1"));
	assert (i1->context == mu::core::context (1, 2, 1, 1, 3, 2));
	assert (e1->full_name->string.empty ());
	assert (e1->individual_names.empty ());
}

void mu::io_test::parser::run_4 ()
{
	mu::io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::parser::parser parser (errors, boost::bind (&mu::io_test::parser_result::operator(), &result, _1));
	parser (new mu::io::tokens::left_square, mu::core::context (1, 1, 0, 1, 1, 0));
	parser (new mu::io::tokens::divider, mu::core::context (1, 2, 1, 1, 2, 1));
	parser (new mu::io::tokens::identifier (std::wstring (L"t1")), mu::core::context (1, 3, 2, 1, 4, 3));
	parser (new mu::io::tokens::right_square, mu::core::context (1, 5, 4, 1, 5, 4));
	auto e1 (boost::dynamic_pointer_cast <mu::io::ast::expression> (result.results [0]));
	assert (e1->values.empty ());
	assert (e1->individual_names.size () == 1);
	assert (e1->context == mu::core::context (1, 1, 0, 1, 5, 4));
	auto i1 (e1->individual_names [0]);
	assert (i1->string == std::wstring (L"t1"));
	assert (e1->full_name->string.empty ());
}

void mu::io_test::parser::run_5 ()
{
	mu::io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::parser::parser parser (errors, boost::bind (&mu::io_test::parser_result::operator(), &result, _1));
	parser (new mu::io::tokens::left_square, mu::core::context (1, 1, 0, 1, 1, 0));
	parser (new mu::io::tokens::divider, mu::core::context (1, 2, 1, 1, 2, 1));
	parser (new mu::io::tokens::divider, mu::core::context (1, 3, 2, 1, 3, 2));
	parser (new mu::io::tokens::identifier (std::wstring (L"t1")), mu::core::context (1, 4, 3, 1, 5, 4));
	parser (new mu::io::tokens::right_square, mu::core::context (1, 6, 5, 1, 6, 5));
	auto e1 (boost::dynamic_pointer_cast <mu::io::ast::expression> (result.results [0]));
	assert (e1->values.empty ());
	assert (e1->individual_names.empty ());
	assert (e1->full_name->string == std::wstring (L"t1"));
	assert (e1->context == mu::core::context (1, 1, 0, 1, 6, 5));
}

void mu::io_test::parser::run_6 ()
{
	mu::io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::parser::parser parser (errors, boost::bind (&mu::io_test::parser_result::operator(), &result, _1));
	parser (new mu::io::tokens::left_square, mu::core::context (1, 1, 0, 1, 1, 0));
	parser (new mu::io::tokens::left_square, mu::core::context (1, 2, 1, 1, 2, 1));
	parser (new mu::io::tokens::right_square, mu::core::context (1, 3, 2, 1, 3, 2));
	parser (new mu::io::tokens::right_square, mu::core::context (1, 4, 3, 1, 4, 3));
	auto e1 (boost::dynamic_pointer_cast <mu::io::ast::expression> (result.results [0]));
	assert (e1->values.size () == 1);
	assert (e1->individual_names.empty ());
	assert (e1->full_name->string.empty ());
	assert (e1->context == mu::core::context (1, 1, 0, 1, 4, 3));
	auto e2 (boost::dynamic_pointer_cast <mu::io::ast::expression> (e1->values [0]));
	assert (e2->values.empty ());
	assert (e2->individual_names.empty ());
	assert (e2->full_name->string.empty ());
	assert (e2->context == mu::core::context (1, 2, 1, 1, 3, 2));
}

void mu::io_test::parser::run_7 ()
{
	mu::io_test::parser_result result;
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::io::parser::parser parser (errors, boost::bind (&mu::io_test::parser_result::operator(), &result, _1));
	parser (new mu::io::tokens::stream_end, mu::core::context (1, 1, 0, 1, 1, 0));
	assert (errors->errors.empty ());
	assert (result.results.size () == 1);
	auto end (boost::dynamic_pointer_cast <mu::io::ast::end> (result.results [0]));
}
