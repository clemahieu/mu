#include "analyzer.h"

#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io_test/analyzer_result.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p/node.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/call.h>
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
	auto routine (result.routines [0]->call);
	assert (routine->dependencies.size () == 2);
	auto parameters (boost::dynamic_pointer_cast <lambda_p::call> (*routine->dependencies.begin ()));
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
	auto routine (result.routines [0]->call);
	assert (routine->dependencies.size () == 2);
	auto parameters (boost::dynamic_pointer_cast <lambda_p::call> (*routine->dependencies.begin ()));
	assert (parameters.get () != nullptr);
	assert (parameters->dependencies.empty ());
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
	auto routine (result.routines [0]->call);
	assert (routine->dependencies.size () == 2);
	auto reference (boost::dynamic_pointer_cast <lambda_p::reference> (*routine->dependencies.begin ()));
	assert (reference.get () != nullptr);
	assert (reference->call->dependencies.empty ());
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
	auto routine (result.routines [0]->call);
	assert (routine->dependencies.size () == 2);
	auto parameters (boost::dynamic_pointer_cast <lambda_p::call> (*routine->dependencies.begin ()));
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
	expression1->full_name = std::wstring (L"a");
	expression2->full_name = std::wstring (L"b");
	expression1->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"b"))));
	expression2->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));
	analyzer_l (expression);
	assert (result.routines.empty ());
	assert (result.errors->errors.size () == 2);	
}