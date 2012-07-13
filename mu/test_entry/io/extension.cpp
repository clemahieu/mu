#include <mu/io/analyzer/analyzer.h>
#include <mu/test_entry/io/analyzer_result.h>
#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_list.h>
#include <mu/test_entry/io/extension1.h>
#include <mu/test_entry/io/extension2.h>
#include <mu/test_entry/io/extension3.h>
#include <mu/test_entry/io/extension4.h>
#include <mu/io/ast/identifier.h>
#include <mu/io/ast/expression.h>
#include <mu/core/expression.h>
#include <mu/core/routine.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/ast/cluster.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <map>

#include <gtest/gtest.h>

TEST (io_test, extension1)
{	
	mu::io_test::analyzer_result result;
	auto extensions (boost::shared_ptr <mu::io::analyzer::extensions::extensions> (new mu::io::analyzer::extensions::extensions));
	extensions->extensions_m [std::wstring (L"a")] = boost::shared_ptr <mu::io::analyzer::extensions::extension> (new mu::io_test::extension1);
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a"))));
	auto cl (boost::make_shared <mu::io::ast::cluster> ());
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	EXPECT_EQ (result.errors->errors.empty (), true);
	EXPECT_EQ (result.clusters.size (), 1);
	auto cluster (result.clusters [0]);
	EXPECT_EQ (cluster->routines.size (), 1);
	auto routine (cluster->routines [0]->body);
	EXPECT_EQ (routine->dependencies.size (), 0);
}

TEST (io_test, extension2)
{	
	mu::io_test::analyzer_result result;
	auto extensions (boost::shared_ptr <mu::io::analyzer::extensions::extensions> (new mu::io::analyzer::extensions::extensions));
	extensions->extensions_m [std::wstring (L"a")] = boost::shared_ptr <mu::io::analyzer::extensions::extension> (new mu::io_test::extension2);
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a"))));
	auto cl (boost::make_shared <mu::io::ast::cluster> ());
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	EXPECT_EQ (result.errors->errors.empty (), true);
	EXPECT_EQ (result.clusters.size (), 1);
	auto cluster (result.clusters [0]);
	EXPECT_EQ (cluster->routines.size (), 1);
	auto routine (cluster->routines [0]->body);
	EXPECT_EQ (routine->dependencies.size (), 1);
}

TEST (io_test, extension3)
{	
	mu::io_test::analyzer_result result;
	auto extensions (boost::shared_ptr <mu::io::analyzer::extensions::extensions> (new mu::io::analyzer::extensions::extensions));
	extensions->extensions_m [std::wstring (L"a")] = boost::shared_ptr <mu::io::analyzer::extensions::extension> (new mu::io_test::extension3);
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a"))));
	auto cl (boost::make_shared <mu::io::ast::cluster> ());
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	EXPECT_EQ (result.errors->errors.empty (), true);
	EXPECT_EQ (result.clusters.size (), 1);
	auto cluster (result.clusters [0]);
	EXPECT_EQ (cluster->routines.size (), 1);
	auto routine (cluster->routines [0]->body);
	EXPECT_EQ (routine->dependencies.size (), 2);
}

TEST (io_test, extension4)
{	
	mu::io_test::analyzer_result result;
	auto extensions (boost::shared_ptr <mu::io::analyzer::extensions::extensions> (new mu::io::analyzer::extensions::extensions));
	extensions->extensions_m [std::wstring (L"a")] = boost::shared_ptr <mu::io::analyzer::extensions::extension> (new mu::io_test::extension4);
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a"))));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"b"))));
	auto cl (boost::make_shared <mu::io::ast::cluster> ());
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	EXPECT_EQ (result.errors->errors.empty (), true);
	EXPECT_EQ (result.clusters.size (), 1);
	auto cluster (result.clusters [0]);
	EXPECT_EQ (cluster->routines.size (), 1);
	auto routine (cluster->routines [0]->body);
	EXPECT_EQ (routine->dependencies.size (), 1);
}