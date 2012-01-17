#include "analyzer.h"

#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io_test/analyzer_result.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_io/ast/parameters.h>
#include <lambda_p/node.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/expression.h>
#include <lambda_p/reference.h>
#include <lambda_p/routine.h>

#include <boost/bind.hpp>

void lambda_p_io_test::analyzer::run ()
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
}

//Test empty expression
void lambda_p_io_test::analyzer::run_1 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	analyzer_l (expression);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());
}

// Test failure, cannot name top level expression
void lambda_p_io_test::analyzer::run_2 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->individual_names.push_back (std::wstring (L"a"));
	analyzer_l (expression);
	assert (result.routines.empty ());
	assert (result.errors->errors.size () == 1);
}

// Test undeclared identifier
void lambda_p_io_test::analyzer::run_3 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));
	analyzer_l (expression);
	assert (result.routines.empty ());
	assert (result.errors->errors.size () == 1);
}

// Test full name reference
void lambda_p_io_test::analyzer::run_4 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	auto expression1 (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression1->full_name = std::wstring (L"~");
	expression->values.push_back (expression1);
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"~"))));
	analyzer_l (expression);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());	
	auto body (result.routines [0]->body);
	assert (body->dependencies.size () == 1);
	auto parameters (boost::dynamic_pointer_cast <lambda_p::expression> (body->dependencies [0]));
	assert (parameters.get () != nullptr);
	assert (parameters->dependencies.empty ());
}

// Test local name reference
void lambda_p_io_test::analyzer::run_5 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	auto expression1 (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression1->individual_names.push_back (std::wstring (L"~"));
	expression->values.push_back (expression1);
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"~"))));
	analyzer_l (expression);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());	
	auto body (result.routines [0]->body);
	assert (body->dependencies.size () == 1);
	auto parameters (boost::dynamic_pointer_cast <lambda_p::reference> (body->dependencies [0]));
	assert (parameters.get () != nullptr);
	assert (parameters->index == 0);
}

// Test out of order name reference
void lambda_p_io_test::analyzer::run_6 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	auto expression1 (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression1->individual_names.push_back (std::wstring (L"~"));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"~"))));
	expression->values.push_back (expression1);
	analyzer_l (expression);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());		
	auto body (result.routines [0]->body);
	assert (body->dependencies.size () == 1);
	auto reference (boost::dynamic_pointer_cast <lambda_p::reference> (body->dependencies [0]));
	assert (reference.get () != nullptr);
	auto call (boost::dynamic_pointer_cast <lambda_p::expression> (reference->expression));
	assert (call.get () != nullptr);
	assert (call->dependencies.empty ());
	assert (reference->index == 0);
}

// Test out of order full name reference
void lambda_p_io_test::analyzer::run_7 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	auto expression1 (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression1->full_name = std::wstring (L"~");
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"~"))));
	expression->values.push_back (expression1);
	analyzer_l (expression);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());		
	auto body (result.routines [0]->body);
	assert (body->dependencies.size () == 1);
	auto parameters (boost::dynamic_pointer_cast <lambda_p::expression> (body->dependencies [0]));
	assert (parameters.get () != nullptr);
	assert (parameters->dependencies.empty ());
}

// Test failure of cyclic reference
void lambda_p_io_test::analyzer::run_8 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	auto expression1 (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	auto expression2 (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (expression1);
	expression->values.push_back (expression2);
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"b"))));
	expression1->full_name = std::wstring (L"a");
	expression2->full_name = std::wstring (L"b");
	expression1->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"b"))));
	expression2->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));
	analyzer_l (expression);
	assert (!result.routines.empty ());
	assert (result.errors->errors.empty ());		
	auto body (result.routines [0]->body);
	assert (body->dependencies.size () == 2);
	auto d1 (boost::dynamic_pointer_cast <lambda_p::expression> (body->dependencies [0]));
	assert (d1.get () != nullptr);
	auto d2 (boost::dynamic_pointer_cast <lambda_p::expression> (body->dependencies [1]));
	assert (d2.get () != nullptr);
	assert (d1->dependencies.size () == 1);
	assert (d2->dependencies.size () == 1);
	assert (d1->dependencies [0] == d2);
	assert (d2->dependencies [0] == d1);
}

// Test parameters
void lambda_p_io_test::analyzer::run_9 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	auto parameters (boost::shared_ptr <lambda_p_io::ast::parameters> (new lambda_p_io::ast::parameters));
	expression->values.push_back (parameters);
	analyzer_l (expression);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());	
	auto body (result.routines [0]->body);
	assert (body->dependencies.size () == 1);
	auto params (boost::dynamic_pointer_cast <lambda_p::node> (body->dependencies [0]));
	assert (params.get () != nullptr);
}

// Resolve multiple identifiers while another remains unresolved
void lambda_p_io_test::analyzer::run_10 ()
{
	// [[unresolved; a] [:~; b] [:~; c] [:~; unresolved] a]
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto parameters (boost::shared_ptr <lambda_p_io::ast::parameters> (new lambda_p_io::ast::parameters));
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	auto e1 (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (e1);
	e1->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"unresolved"))));
	e1->individual_names.push_back (std::wstring (L"a"));
	auto e2 (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (e2);
	e2->values.push_back (parameters);
	e2->individual_names.push_back (std::wstring (L"b"));
	auto e3 (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (e3);
	e3->values.push_back (parameters);
	e3->individual_names.push_back (std::wstring (L"c"));
	auto e4 (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (e4);
	e4->values.push_back (parameters);
	e4->individual_names.push_back (std::wstring (L"unresolved"));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));	
	analyzer_l (expression);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());	
}

// With more than one unresolved identifier, resolve lesser then greater
void lambda_p_io_test::analyzer::run_11 ()
{
	// [[un1 un2] [:~; un1] [:~; un2]]
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (&lambda_p_io_test::analyzer_result::operator(), &result, _1), result.errors);
	auto parameters (boost::shared_ptr <lambda_p_io::ast::parameters> (new lambda_p_io::ast::parameters));
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	auto e1 (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (e1);
	e1->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"un1"))));
	e1->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"un2"))));
	auto e2 (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (e2);
	e2->values.push_back (parameters);
	e2->individual_names.push_back (std::wstring (L"un1"));
	auto e3 (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (e3);
	e3->values.push_back (parameters);
	e3->individual_names.push_back (std::wstring (L"un2"));
	analyzer_l (expression);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());	
}