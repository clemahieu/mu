#include "extension.h"

#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io_test/analyzer_result.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/end.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_io_test/extension1.h>
#include <lambda_p_io_test/extension2.h>
#include <lambda_p_io_test/extension3.h>
#include <lambda_p_io_test/extension4.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/expression.h>
#include <lambda_p/routine.h>
#include <lambda_p_io/analyzer/extensions/extensions.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

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
	auto extensions (boost::shared_ptr <lambda_p_io::analyzer::extensions::extensions> (new lambda_p_io::analyzer::extensions::extensions));
	extensions->extensions_m [std::wstring (L"a")] = boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io_test::extension1);
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (lambda_p::context (), std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (lambda_p::context (), std::wstring (L"a"))));
	expression->full_name = boost::make_shared <lambda_p_io::ast::identifier> (lambda_p::context (), std::wstring (L"1"));
	analyzer_l.input (expression);
	analyzer_l.input (boost::make_shared <lambda_p_io::ast::end> (lambda_p::context ()));
	assert (result.errors->errors.empty ());
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [std::wstring (L"1")]->body);
	assert (routine->dependencies.size () == 0);
}

void lambda_p_io_test::extension::run_2 ()
{	
	lambda_p_io_test::analyzer_result result;
	auto extensions (boost::shared_ptr <lambda_p_io::analyzer::extensions::extensions> (new lambda_p_io::analyzer::extensions::extensions));
	extensions->extensions_m [std::wstring (L"a")] = boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io_test::extension2);
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (lambda_p::context (), std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (lambda_p::context (), std::wstring (L"a"))));
	expression->full_name = boost::make_shared <lambda_p_io::ast::identifier> (lambda_p::context (), std::wstring (L"1"));
	analyzer_l.input (expression);
	analyzer_l.input (boost::make_shared <lambda_p_io::ast::end> (lambda_p::context ()));
	assert (result.errors->errors.empty ());
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [std::wstring (L"1")]->body);
	assert (routine->dependencies.size () == 1);
}

void lambda_p_io_test::extension::run_3 ()
{	
	lambda_p_io_test::analyzer_result result;
	auto extensions (boost::shared_ptr <lambda_p_io::analyzer::extensions::extensions> (new lambda_p_io::analyzer::extensions::extensions));
	extensions->extensions_m [std::wstring (L"a")] = boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io_test::extension3);
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (lambda_p::context (), std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (lambda_p::context (), std::wstring (L"a"))));
	expression->full_name = boost::make_shared <lambda_p_io::ast::identifier> (lambda_p::context (), std::wstring (L"1"));
	analyzer_l.input (expression);
	analyzer_l.input (boost::make_shared <lambda_p_io::ast::end> (lambda_p::context ()));
	assert (result.errors->errors.empty ());
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [std::wstring (L"1")]->body);
	assert (routine->dependencies.size () == 2);
}

void lambda_p_io_test::extension::run_4 ()
{	
	lambda_p_io_test::analyzer_result result;
	auto extensions (boost::shared_ptr <lambda_p_io::analyzer::extensions::extensions> (new lambda_p_io::analyzer::extensions::extensions));
	extensions->extensions_m [std::wstring (L"a")] = boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io_test::extension4);
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (lambda_p::context (), std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (lambda_p::context (), std::wstring (L"a"))));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (lambda_p::context (), std::wstring (L"b"))));
	expression->full_name = boost::make_shared <lambda_p_io::ast::identifier> (lambda_p::context (), std::wstring (L"1"));
	analyzer_l.input (expression);
	analyzer_l.input (boost::make_shared <lambda_p_io::ast::end> (lambda_p::context ()));
	assert (result.errors->errors.empty ());
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [std::wstring (L"1")]->body);
	assert (routine->dependencies.size () == 1);
}