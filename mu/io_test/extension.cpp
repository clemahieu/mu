#include "extension.h"

#include <mu/io/analyzer/analyzer.h>
#include <mu/io_test/analyzer_result.h>
#include <mu/io/ast/expression.h>
#include <mu/io/ast/end.h>
#include <mu/core/errors/error_list.h>
#include <mu/io_test/extension1.h>
#include <mu/io_test/extension2.h>
#include <mu/io_test/extension3.h>
#include <mu/io_test/extension4.h>
#include <mu/io/ast/identifier.h>
#include <mu/io/ast/expression.h>
#include <mu/core/expression.h>
#include <mu/core/routine.h>
#include <mu/io/analyzer/extensions/extensions.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <map>

void mu::io_test::extension::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void mu::io_test::extension::run_1 ()
{	
	mu::io_test::analyzer_result result;
	auto extensions (boost::shared_ptr <mu::io::analyzer::extensions::extensions> (new mu::io::analyzer::extensions::extensions));
	extensions->extensions_m [std::wstring (L"a")] = boost::shared_ptr <mu::io::analyzer::extensions::extension> (new mu::io_test::extension1);
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1, _2), result.errors, extensions);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a"))));
	analyzer_l.input (expression);
	analyzer_l.input (boost::make_shared <mu::io::ast::end> (mu::io::debugging::context ()));
	assert (result.errors->errors.empty ());
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]->body);
	assert (routine->dependencies.size () == 0);
}

void mu::io_test::extension::run_2 ()
{	
	mu::io_test::analyzer_result result;
	auto extensions (boost::shared_ptr <mu::io::analyzer::extensions::extensions> (new mu::io::analyzer::extensions::extensions));
	extensions->extensions_m [std::wstring (L"a")] = boost::shared_ptr <mu::io::analyzer::extensions::extension> (new mu::io_test::extension2);
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1, _2), result.errors, extensions);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a"))));
	analyzer_l.input (expression);
	analyzer_l.input (boost::make_shared <mu::io::ast::end> (mu::io::debugging::context ()));
	assert (result.errors->errors.empty ());
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]->body);
	assert (routine->dependencies.size () == 1);
}

void mu::io_test::extension::run_3 ()
{	
	mu::io_test::analyzer_result result;
	auto extensions (boost::shared_ptr <mu::io::analyzer::extensions::extensions> (new mu::io::analyzer::extensions::extensions));
	extensions->extensions_m [std::wstring (L"a")] = boost::shared_ptr <mu::io::analyzer::extensions::extension> (new mu::io_test::extension3);
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1, _2), result.errors, extensions);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a"))));
	analyzer_l.input (expression);
	analyzer_l.input (boost::make_shared <mu::io::ast::end> (mu::io::debugging::context ()));
	assert (result.errors->errors.empty ());
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]->body);
	assert (routine->dependencies.size () == 2);
}

void mu::io_test::extension::run_4 ()
{	
	mu::io_test::analyzer_result result;
	auto extensions (boost::shared_ptr <mu::io::analyzer::extensions::extensions> (new mu::io::analyzer::extensions::extensions));
	extensions->extensions_m [std::wstring (L"a")] = boost::shared_ptr <mu::io::analyzer::extensions::extension> (new mu::io_test::extension4);
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1, _2), result.errors, extensions);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a"))));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"b"))));
	analyzer_l.input (expression);
	analyzer_l.input (boost::make_shared <mu::io::ast::end> (mu::io::debugging::context ()));
	assert (result.errors->errors.empty ());
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]->body);
	assert (routine->dependencies.size () == 1);
}