#include <mu/io/analyzer/analyzer.h>
#include <mu/test_entry/io/analyzer_result.h>
#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>
#include <mu/io/ast/parameters.h>
#include <mu/core/node.h>
#include <mu/core/errors/error_list.h>
#include <mu/core/expression.h>
#include <mu/core/reference.h>
#include <mu/core/routine.h>
#include <mu/io/ast/cluster.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

//Test empty expression
TEST (io_test, analyzer1)
{
	// []
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (1, 1, 0, 1, 2, 1), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 3, 2)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
    EXPECT_EQ (result.clusters.size (), 1);
	auto cluster (result.clusters [0]);
    EXPECT_EQ (cluster->routines.size (), 1);
	auto routine (cluster->routines [0]);
    EXPECT_EQ (result.errors->errors.empty (), true);
}

// Test failure, cannot name top level expression
TEST (io_test, analyzer2)
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->individual_names.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a")));
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 3, 2)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
    EXPECT_EQ (result.clusters.empty (), true);
    EXPECT_EQ (!result.errors->errors.empty (), true);
}

// Test undeclared identifier
TEST (io_test, analyzer3)
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a")));
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 3, 2)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
    EXPECT_EQ (result.clusters.empty (), true);
    EXPECT_EQ (!result.errors->errors.empty (), true);
}

// Test full name reference
TEST (io_test, analyzer4)
{
	// [[;;~]~]
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (1, 1, 0, 1, 8, 7), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto expression1 (new (GC) mu::io::ast::expression (mu::io::debugging::context (1, 2, 1, 1, 6, 5), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression1->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (1, 5, 4, 1, 5, 4), std::wstring (L"~"));
	expression->values.push_back (expression1);
	expression->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (1, 7, 6, 1, 7, 6), std::wstring (L"~")));
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 9, 8)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
    EXPECT_EQ (result.clusters.size (), 1);
	auto cluster (result.clusters [0]);
    EXPECT_EQ (cluster->routines.size (), 1);
    EXPECT_EQ (result.errors->errors.empty (), true);
	auto routine (cluster->routines [0]);
	auto body (cluster->routines [0]->body);
    EXPECT_EQ (body->dependencies.size (), 1);
	auto parameters (dynamic_cast <mu::core::expression *> (body->dependencies [0]));
    EXPECT_NE (parameters, nullptr);
    EXPECT_EQ (parameters->dependencies.empty (), true);
}

// Test local name reference
TEST (io_test, analyzer5)
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto expression1 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression1->individual_names.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"~")));
	expression->values.push_back (expression1);
	expression->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"~")));
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
    EXPECT_EQ (result.clusters.size (), 1);
	auto cluster (result.clusters [0]);
    EXPECT_EQ (cluster->routines.size (), 1);
    EXPECT_EQ (result.errors->errors.empty (), true);
	auto body (cluster->routines [0]->body);
    EXPECT_EQ (body->dependencies.size (), 1);
	auto parameters (dynamic_cast <mu::core::reference *> (body->dependencies [0]));
    EXPECT_NE (parameters, nullptr);
    EXPECT_EQ (parameters->index, 0);
}

// Test out of order name reference
TEST (io_test, analyzer6)
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto expression1 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression1->individual_names.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"~")));
	expression->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"~")));
	expression->values.push_back (expression1);
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
    EXPECT_EQ (result.clusters.size (), 1);
	auto cluster (result.clusters [0]);
    EXPECT_EQ (result.errors->errors.empty (), true);
	auto body (cluster->routines [0]->body);
    EXPECT_EQ (body->dependencies.size (), 1);
	auto reference (dynamic_cast <mu::core::reference *> (body->dependencies [0]));
    EXPECT_NE (reference, nullptr);
	auto call (dynamic_cast <mu::core::expression *> (reference->expression));
    EXPECT_NE (call, nullptr);
    EXPECT_EQ (call->dependencies.empty (), true);
    EXPECT_EQ (reference->index, 0);
}

// Test out of order full name reference
TEST (io_test, analyzer7)
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto expression1 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression1->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"~"));
	expression->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"~")));
	expression->values.push_back (expression1);
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
    EXPECT_EQ (result.clusters.size (), 1);
	auto cluster (result.clusters [0]);
    EXPECT_EQ (result.errors->errors.empty (), true);
	auto body (cluster->routines [0]->body);
    EXPECT_EQ (body->dependencies.size (), 1);
	auto parameters (dynamic_cast <mu::core::expression *> (body->dependencies [0]));
    EXPECT_NE (parameters, nullptr);
    EXPECT_EQ (parameters->dependencies.empty (), true);
}

// Test failure of cyclic reference
TEST (io_test, analyzer8)
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto expression1 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto expression2 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->values.push_back (expression1);
	expression->values.push_back (expression2);
	expression->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a")));
	expression->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"b")));
	expression1->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a"));
	expression2->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"b"));
	expression1->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"b")));
	expression2->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a")));
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
    EXPECT_EQ (!result.clusters.empty (), true);
    EXPECT_EQ (result.errors->errors.empty (), true);
	auto cluster (result.clusters [0]);
	auto body (cluster->routines [0]->body);
    EXPECT_EQ (body->dependencies.size (), 2);
	auto d1 (dynamic_cast <mu::core::expression *> (body->dependencies [0]));
    EXPECT_NE (d1, nullptr);
	auto d2 (dynamic_cast <mu::core::expression *> (body->dependencies [1]));
    EXPECT_NE (d2, nullptr);
    EXPECT_EQ (d1->dependencies.size (), 1);
    EXPECT_EQ (d2->dependencies.size (), 1);
    EXPECT_EQ (d1->dependencies [0], d2);
    EXPECT_EQ (d2->dependencies [0], d1);
}

// Test parameters
TEST (io_test, analyzer9)
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto parameters (new (GC) mu::io::ast::parameters (mu::io::debugging::context ()));
	expression->values.push_back (parameters);
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
    EXPECT_EQ (result.clusters.size (), 1);
	auto cluster (result.clusters [0]);
    EXPECT_EQ (result.errors->errors.empty (), true);
	auto body (cluster->routines [0]->body);
    EXPECT_EQ (body->dependencies.size (), 1);
	auto params (dynamic_cast <mu::core::node *> (body->dependencies [0]));
    EXPECT_NE (params, nullptr);
}

// Resolve multiple identifiers while another remains unresolved
TEST (io_test, analyzer10)
{
	// [[unresolved; a] [:~; b] [:~; c] [:~; unresolved] a]
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto parameters (new (GC) mu::io::ast::parameters (mu::io::debugging::context ()));
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto e1 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->values.push_back (e1);
	e1->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"unresolved")));
	e1->individual_names.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a")));
	auto e2 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->values.push_back (e2);
	e2->values.push_back (parameters);
	e2->individual_names.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"b")));
	auto e3 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->values.push_back (e3);
	e3->values.push_back (parameters);
	e3->individual_names.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"c")));
	auto e4 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->values.push_back (e4);
	e4->values.push_back (parameters);
	e4->individual_names.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"unresolved")));
	expression->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a")));	
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
    EXPECT_EQ (result.clusters.size (), 1);
    EXPECT_EQ (result.errors->errors.empty (), true);
}

// With more than one unresolved identifier, resolve lesser then greater
TEST (io_test, analyzer11)
{
	// [[un1 un2] [:~; un1] [:~; un2]]
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto parameters (new (GC) mu::io::ast::parameters (mu::io::debugging::context ()));
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto e1 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->values.push_back (e1);
	e1->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"un1")));
	e1->values.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"un2")));
	auto e2 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->values.push_back (e2);
	e2->values.push_back (parameters);
	e2->individual_names.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"un1")));
	auto e3 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->values.push_back (e3);
	e3->values.push_back (parameters);
	e3->individual_names.push_back (new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"un2")));
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
    EXPECT_EQ (result.clusters.size (), 1);
    EXPECT_EQ (result.errors->errors.empty (), true);
}

//Test local naming after routine name declared
TEST (io_test, analyzer12)
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"1"));
	auto expression1 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto expression2 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression2->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"1"));
	expression1->values.push_back (expression2);
	expression1->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"2"));
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	cl->expressions.push_back (expression1);
	analyzer_l.input (cl);
    EXPECT_EQ (!result.errors->errors.empty (), true);
}

//Test routine name declaration after local naming
TEST (io_test, analyzer13)
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"1"));
	auto expression2 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression2->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"2"));
	expression->values.push_back (expression2);
	auto expression1 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression1->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"2"));
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	cl->expressions.push_back (expression1);
	analyzer_l.input (cl);
    EXPECT_EQ (!result.errors->errors.empty (), true);
}

//Test routine name collision
TEST (io_test, analyzer14)
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"1"));
	auto expression1 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression1->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"1"));
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	cl->expressions.push_back (expression1);
	analyzer_l.input (cl);
    EXPECT_EQ (!result.errors->errors.empty (), true);
}

//Test no collision between local names in different routines
TEST (io_test, analyzer15)
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto expression2 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression2->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"3"));
	expression->values.push_back (expression2);
	expression->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"1"));
	auto expression1 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto expression3 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression3->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"3"));
	expression1->values.push_back (expression3);
	expression1->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"2"));
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	cl->expressions.push_back (expression1);
	analyzer_l.input (cl);
    EXPECT_EQ (result.errors->errors.empty (), true);
}

//Test duplicate local name
TEST (io_test, analyzer16)
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	auto expression2 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression2->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"2"));
	expression->values.push_back (expression2);
	auto expression3 (new (GC) mu::io::ast::expression (mu::io::debugging::context (), std::vector <mu::io::ast::node *, gc_allocator <mu::io::ast::node *>> ()));
	expression3->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"2"));
	expression->values.push_back (expression3);
	expression->full_name = new (GC) mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"1"));
	auto cl (new (GC) mu::io::ast::cluster (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
    EXPECT_EQ (!result.errors->errors.empty (), true);
}
