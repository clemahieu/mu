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

#include <map>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (io_test, extension1)
{	
	mu::io_test::analyzer_result result;
	auto extensions (new (GC) mu::io::analyzer::extensions::extensions);
	(*extensions) [mu::string (U"a")] = new (GC) mu::io_test::extension1;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), mu::string (U"a")));
	auto cl (new (GC) mu::io::ast::cluster);
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
	auto extensions (new (GC) mu::io::analyzer::extensions::extensions);
	(*extensions) [mu::string (U"a")] = new (GC) mu::io_test::extension2;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), mu::string (U"a")));
	auto cl (new (GC) mu::io::ast::cluster);
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
	auto extensions (new (GC) mu::io::analyzer::extensions::extensions);
	(*extensions) [mu::string (U"a")] = new (GC) mu::io_test::extension3;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), mu::string (U"a")));
	auto cl (new (GC) mu::io::ast::cluster);
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
	auto extensions (new (GC) mu::io::analyzer::extensions::extensions);
	(*extensions) [mu::string (U"a")] = new (GC) mu::io_test::extension4;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors, extensions);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), mu::string (U"a")));
	expression->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), mu::string (U"b")));
	auto cl (new (GC) mu::io::ast::cluster);
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	EXPECT_EQ (result.errors->errors.empty (), true);
	EXPECT_EQ (result.clusters.size (), 1);
	auto cluster (result.clusters [0]);
	EXPECT_EQ (cluster->routines.size (), 1);
	auto routine (cluster->routines [0]->body);
	EXPECT_EQ (routine->dependencies.size (), 1);
}