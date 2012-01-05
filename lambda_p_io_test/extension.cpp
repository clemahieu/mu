#include "extension.h"

#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io_test/analyzer_result.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_io_test/extension1.h>
#include <lambda_p_io_test/extension2.h>
#include <lambda_p_io_test/extension3.h>
#include <lambda_p_io_test/extension4.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/expression.h>

#include <boost/bind.hpp>

#include <map>

void lambda_p_io_test::extension::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_io_test::extension::run_1 ()
{	
	lambda_p_io_test::analyzer_result result;
	std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>> extensions;
	extensions [std::wstring (L"a")] = boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_io_test::extension1);
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));
	analyzer_l (expression);
	assert (result.errors->errors.empty ());
	assert (result.routines.size () == 1);
	auto routine (result.routines [0]);
	assert (routine->dependencies.size () == 0);
}

void lambda_p_io_test::extension::run_2 ()
{	
	lambda_p_io_test::analyzer_result result;
	std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>> extensions;
	extensions [std::wstring (L"a")] = boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_io_test::extension2);
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));
	analyzer_l (expression);
	assert (result.errors->errors.empty ());
	assert (result.routines.size () == 1);
	auto routine (result.routines [0]);
	assert (routine->dependencies.size () == 1);
}

void lambda_p_io_test::extension::run_3 ()
{	
	lambda_p_io_test::analyzer_result result;
	std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>> extensions;
	extensions [std::wstring (L"a")] = boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_io_test::extension3);
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));
	analyzer_l (expression);
	assert (result.errors->errors.empty ());
	assert (result.routines.size () == 1);
	auto routine (result.routines [0]);
	assert (routine->dependencies.size () == 2);
}

void lambda_p_io_test::extension::run_4 ()
{	
	lambda_p_io_test::analyzer_result result;
	std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>> extensions;
	extensions [std::wstring (L"a")] = boost::shared_ptr <lambda_p_io::analyzer::extension> (new lambda_p_io_test::extension4);
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"b"))));
	analyzer_l (expression);
	assert (result.errors->errors.empty ());
	assert (result.routines.size () == 1);
	auto routine (result.routines [0]);
	assert (routine->dependencies.size () == 1);
}