#include <mu/io_test/analyzer.h>

#include <mu/io/analyzer/analyzer.h>
#include <mu/io_test/analyzer_result.h>
#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>
#include <mu/io/ast/parameters.h>
#include <mu/core/node.h>
#include <mu/core/errors/error_list.h>
#include <mu/core/expression.h>
#include <mu/core/reference.h>
#include <mu/core/routine.h>
#include <mu/io/debugging/stream.h>
#include <mu/io/ast/cluster.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

void mu::io_test::analyzer::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
	run_8 ();
	run_9 ();
	run_10 ();
	run_11 ();
	run_12 ();
	run_13 ();
	run_14 ();
	run_15 ();
	run_16 ();
}

//Test empty expression
void mu::io_test::analyzer::run_1 ()
{
	// []
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (1, 1, 0, 1, 2, 1), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 3, 2)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
	assert (result.errors->errors.empty ());
}

// Test failure, cannot name top level expression
void mu::io_test::analyzer::run_2 ()
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->individual_names.push_back (boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"a")));
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 3, 2)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	assert (result.clusters.empty ());
	assert (!result.errors->errors.empty ());
}

// Test undeclared identifier
void mu::io_test::analyzer::run_3 ()
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a"))));
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 3, 2)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	assert (result.clusters.empty ());
	assert (!result.errors->errors.empty ());
}

// Test full name reference
void mu::io_test::analyzer::run_4 ()
{
	// [[;;~]~]
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (1, 1, 0, 1, 8, 7), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	auto expression1 (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (1, 2, 1, 1, 6, 5), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression1->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (1, 5, 4, 1, 5, 4), std::wstring (L"~"));
	expression->values.push_back (expression1);
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (1, 7, 6, 1, 7, 6), std::wstring (L"~"))));
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 9, 8)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (cluster->routines.size () == 1);
	assert (result.errors->errors.empty ());
	auto routine (cluster->routines [0]);
	auto body (cluster->routines [0]->body);
	assert (body->dependencies.size () == 1);
	auto parameters (boost::dynamic_pointer_cast <mu::core::expression> (body->dependencies [0]));
	assert (parameters.get () != nullptr);
	assert (parameters->dependencies.empty ());
}

// Test local name reference
void mu::io_test::analyzer::run_5 ()
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	auto expression1 (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression1->individual_names.push_back (boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"~")));
	expression->values.push_back (expression1);
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"~"))));
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (cluster->routines.size () == 1);
	assert (result.errors->errors.empty ());	
	auto body (cluster->routines [0]->body);
	assert (body->dependencies.size () == 1);
	auto parameters (boost::dynamic_pointer_cast <mu::core::reference> (body->dependencies [0]));
	assert (parameters.get () != nullptr);
	assert (parameters->index == 0);
}

// Test out of order name reference
void mu::io_test::analyzer::run_6 ()
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	auto expression1 (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression1->individual_names.push_back (boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"~")));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"~"))));
	expression->values.push_back (expression1);
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (result.errors->errors.empty ());		
	auto body (cluster->routines [0]->body);
	assert (body->dependencies.size () == 1);
	auto reference (boost::dynamic_pointer_cast <mu::core::reference> (body->dependencies [0]));
	assert (reference.get () != nullptr);
	auto call (boost::dynamic_pointer_cast <mu::core::expression> (reference->expression));
	assert (call.get () != nullptr);
	assert (call->dependencies.empty ());
	assert (reference->index == 0);
}

// Test out of order full name reference
void mu::io_test::analyzer::run_7 ()
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	auto expression1 (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression1->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"~"));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"~"))));
	expression->values.push_back (expression1);
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (result.errors->errors.empty ());		
	auto body (cluster->routines [0]->body);
	assert (body->dependencies.size () == 1);
	auto parameters (boost::dynamic_pointer_cast <mu::core::expression> (body->dependencies [0]));
	assert (parameters.get () != nullptr);
	assert (parameters->dependencies.empty ());
}

// Test failure of cyclic reference
void mu::io_test::analyzer::run_8 ()
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	auto expression1 (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	auto expression2 (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (expression1);
	expression->values.push_back (expression2);
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a"))));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"b"))));
	expression1->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"a"));
	expression2->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"b"));
	expression1->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"b"))));
	expression2->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a"))));
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	assert (!result.clusters.empty ());
	assert (result.errors->errors.empty ());		
	auto cluster (result.clusters [0]);
	auto body (cluster->routines [0]->body);
	assert (body->dependencies.size () == 2);
	auto d1 (boost::dynamic_pointer_cast <mu::core::expression> (body->dependencies [0]));
	assert (d1.get () != nullptr);
	auto d2 (boost::dynamic_pointer_cast <mu::core::expression> (body->dependencies [1]));
	assert (d2.get () != nullptr);
	assert (d1->dependencies.size () == 1);
	assert (d2->dependencies.size () == 1);
	assert (d1->dependencies [0] == d2);
	assert (d2->dependencies [0] == d1);
}

// Test parameters
void mu::io_test::analyzer::run_9 ()
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	auto parameters (boost::shared_ptr <mu::io::ast::parameters> (new mu::io::ast::parameters (mu::io::debugging::context ())));
	expression->values.push_back (parameters);
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	assert (result.clusters.size () == 1);
	auto cluster (result.clusters [0]);
	assert (result.errors->errors.empty ());	
	auto body (cluster->routines [0]->body);
	assert (body->dependencies.size () == 1);
	auto params (boost::dynamic_pointer_cast <mu::core::node> (body->dependencies [0]));
	assert (params.get () != nullptr);
}

// Resolve multiple identifiers while another remains unresolved
void mu::io_test::analyzer::run_10 ()
{
	// [[unresolved; a] [:~; b] [:~; c] [:~; unresolved] a]
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto parameters (boost::shared_ptr <mu::io::ast::parameters> (new mu::io::ast::parameters (mu::io::debugging::context ())));
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	auto e1 (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (e1);
	e1->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"unresolved"))));
	e1->individual_names.push_back (boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"a")));
	auto e2 (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (e2);
	e2->values.push_back (parameters);
	e2->individual_names.push_back (boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"b")));
	auto e3 (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (e3);
	e3->values.push_back (parameters);
	e3->individual_names.push_back (boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"c")));
	auto e4 (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (e4);
	e4->values.push_back (parameters);
	e4->individual_names.push_back (boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"unresolved")));
	expression->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"a"))));	
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	assert (result.clusters.size () == 1);
	assert (result.errors->errors.empty ());	
}

// With more than one unresolved identifier, resolve lesser then greater
void mu::io_test::analyzer::run_11 ()
{
	// [[un1 un2] [:~; un1] [:~; un2]]
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto parameters (boost::shared_ptr <mu::io::ast::parameters> (new mu::io::ast::parameters (mu::io::debugging::context ())));
	auto expression (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	auto e1 (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (e1);
	e1->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"un1"))));
	e1->values.push_back (boost::shared_ptr <mu::io::ast::identifier> (new mu::io::ast::identifier (mu::io::debugging::context (), std::wstring (L"un2"))));
	auto e2 (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (e2);
	e2->values.push_back (parameters);
	e2->individual_names.push_back (boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"un1")));
	auto e3 (boost::shared_ptr <mu::io::ast::expression> (new mu::io::ast::expression (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ())));
	expression->values.push_back (e3);
	e3->values.push_back (parameters);
	e3->individual_names.push_back (boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"un2")));
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	assert (result.clusters.size () == 1);
	assert (result.errors->errors.empty ());	
}

//Test local naming after routine name declared
void mu::io_test::analyzer::run_12 ()
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	expression->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"1"));
	auto expression1 (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	auto expression2 (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	expression2->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"1"));
	expression1->values.push_back (expression2);
	expression1->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"2"));
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	cl->expressions.push_back (expression1);
	analyzer_l.input (cl);
	assert (!result.errors->errors.empty ());
}

//Test routine name declaration after local naming
void mu::io_test::analyzer::run_13 ()
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	expression->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"1"));
	auto expression2 (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	expression2->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"2"));
	expression->values.push_back (expression2);
	auto expression1 (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	expression1->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"2"));
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	cl->expressions.push_back (expression1);
	analyzer_l.input (cl);
	assert (!result.errors->errors.empty ());
}

//Test routine name collision
void mu::io_test::analyzer::run_14 ()
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	expression->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"1"));
	auto expression1 (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	expression1->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"1"));
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	cl->expressions.push_back (expression1);
	analyzer_l.input (cl);
	assert (!result.errors->errors.empty ());
}

//Test no collision between local names in different routines
void mu::io_test::analyzer::run_15 ()
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	auto expression2 (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	expression2->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"3"));
	expression->values.push_back (expression2);
	expression->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"1"));
	auto expression1 (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	auto expression3 (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	expression3->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"3"));
	expression1->values.push_back (expression3);
	expression1->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"2"));
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	cl->expressions.push_back (expression1);
	analyzer_l.input (cl);
	assert (result.errors->errors.empty ());
}

//Test duplicate local name
void mu::io_test::analyzer::run_16 ()
{
	mu::io_test::analyzer_result result;
	mu::io::analyzer::analyzer analyzer_l (boost::bind (&mu::io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	auto expression2 (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	expression2->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"2"));
	expression->values.push_back (expression2);
	auto expression3 (boost::make_shared <mu::io::ast::expression> (mu::io::debugging::context (), std::vector <boost::shared_ptr <mu::io::ast::node>> ()));
	expression3->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"2"));
	expression->values.push_back (expression3);
	expression->full_name = boost::make_shared <mu::io::ast::identifier> (mu::io::debugging::context (), std::wstring (L"1"));
	auto cl (boost::make_shared <mu::io::ast::cluster> (mu::io::debugging::context (1, 1, 0, 1, 1, 0)));
	cl->expressions.push_back (expression);
	analyzer_l.input (cl);
	assert (!result.errors->errors.empty ());
}