#include "analyzer.h"

#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io_test/analyzer_result.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/container.h>
#include <lambda_p/core/entry.h>
#include <lambda_p/core/node.h>
#include <lambda_p/core/pipe.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/core/data.h>

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
	run_12 ();
}

void lambda_p_io_test::analyzer::run_1 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (static_cast <void (lambda_p_io_test::analyzer_result::*)(boost::shared_ptr <lambda_p::core::routine>)> (&lambda_p_io_test::analyzer_result::operator()), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L".identity"))));
	analyzer_l (expression);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());
}

void lambda_p_io_test::analyzer::run_2 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (static_cast <void (lambda_p_io_test::analyzer_result::*)(boost::shared_ptr <lambda_p::core::routine>)> (&lambda_p_io_test::analyzer_result::operator()), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->individual_names.push_back (std::wstring (L"a"));
	analyzer_l (expression);
	assert (result.routines.empty ());
	assert (result.errors->errors.size () == 1);
}

void lambda_p_io_test::analyzer::run_3 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (static_cast <void (lambda_p_io_test::analyzer_result::*)(boost::shared_ptr <lambda_p::core::routine>)> (&lambda_p_io_test::analyzer_result::operator()), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));
	analyzer_l (expression);
	assert (result.routines.empty ());
	assert (result.errors->errors.size () == 1);
}

void lambda_p_io_test::analyzer::run_4 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (static_cast <void (lambda_p_io_test::analyzer_result::*)(boost::shared_ptr <lambda_p::core::routine>)> (&lambda_p_io_test::analyzer_result::operator()), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"b"))));
	analyzer_l (expression);
	assert (result.routines.empty ());
	assert (result.errors->errors.size () == 2);
}

void lambda_p_io_test::analyzer::run_5 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (static_cast <void (lambda_p_io_test::analyzer_result::*)(boost::shared_ptr <lambda_p::core::routine>)> (&lambda_p_io_test::analyzer_result::operator()), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"~"))));
	analyzer_l (expression);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());	
}

void lambda_p_io_test::analyzer::run_6 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (static_cast <void (lambda_p_io_test::analyzer_result::*)(boost::shared_ptr <lambda_p::core::routine>)> (&lambda_p_io_test::analyzer_result::operator()), &result, _1), result.errors);
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"~"))));
	analyzer_l (expression);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());	
	auto routine (result.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	routine->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::node>> arguments;
	arguments.push_back (boost::shared_ptr <lambda_p::core::node> (new lambda_p::core::node));
	(*routine->input) (arguments);
	assert (result.errors->errors.empty ());
	assert (container->results.size () == 1);
	assert (container->results [0] == arguments [0]);
}

void lambda_p_io_test::analyzer::run_7 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (static_cast <void (lambda_p_io_test::analyzer_result::*)(boost::shared_ptr <lambda_p::core::routine>)> (&lambda_p_io_test::analyzer_result::operator()), &result, _1), result.errors);
	auto expression_top (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression_top->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L".identity"))));
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression_top->values.push_back (expression);
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"~"))));
	expression->full_name = std::wstring (L"a");
	analyzer_l (expression_top);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());	
	auto routine (result.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	routine->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::node>> arguments;
	arguments.push_back (boost::shared_ptr <lambda_p::core::node> (new lambda_p::core::node));
	(*routine->input) (arguments);
	assert (result.errors->errors.empty ());
	assert (container->results.empty ());
}

void lambda_p_io_test::analyzer::run_8 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (static_cast <void (lambda_p_io_test::analyzer_result::*)(boost::shared_ptr <lambda_p::core::routine>)> (&lambda_p_io_test::analyzer_result::operator()), &result, _1), result.errors);
	auto expression_top (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression_top->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L".identity"))));
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression_top->values.push_back (expression);
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"~"))));
	expression->full_name = std::wstring (L"a");
	analyzer_l (expression_top);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());	
	auto routine (result.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	routine->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::node>> arguments;
	arguments.push_back (boost::shared_ptr <lambda_p::core::node> (new lambda_p::core::node));
	(*routine->input) (arguments);
	assert (result.errors->errors.empty ());
	assert (container->results.empty ());
}

void lambda_p_io_test::analyzer::run_9 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (static_cast <void (lambda_p_io_test::analyzer_result::*)(boost::shared_ptr <lambda_p::core::routine>)> (&lambda_p_io_test::analyzer_result::operator()), &result, _1), result.errors);
	auto expression_top (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression_top->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L".identity"))));
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression_top->values.push_back (expression);
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"~"))));
	expression->individual_names.push_back (std::wstring (L"a"));
	analyzer_l (expression_top);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());	
	auto routine (result.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	routine->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::node>> arguments;
	arguments.push_back (boost::shared_ptr <lambda_p::core::node> (new lambda_p::core::node));
	(*routine->input) (arguments);
	assert (result.errors->errors.empty ());
	assert (container->results.empty ());
}

void lambda_p_io_test::analyzer::run_10 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (static_cast <void (lambda_p_io_test::analyzer_result::*)(boost::shared_ptr <lambda_p::core::routine>)> (&lambda_p_io_test::analyzer_result::operator()), &result, _1), result.errors);
	auto expression_top (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression_top->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L".identity"))));
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression_top->values.push_back (expression);
	expression_top->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"~"))));
	expression->individual_names.push_back (std::wstring (L"a"));
	analyzer_l (expression_top);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());	
	auto routine (result.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	routine->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::node>> arguments;
	arguments.push_back (boost::shared_ptr <lambda_p::core::node> (new lambda_p::core::node));
	(*routine->input) (arguments);
	assert (result.errors->errors.empty ());
	assert (container->results.size () == 1);
	assert (container->results [0] == arguments [0]);
}

void lambda_p_io_test::analyzer::run_11 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (static_cast <void (lambda_p_io_test::analyzer_result::*)(boost::shared_ptr <lambda_p::core::routine>)> (&lambda_p_io_test::analyzer_result::operator()), &result, _1), result.errors);
	auto expression_top (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression_top->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L".identity"))));
	expression_top->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));
	auto expression (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression_top->values.push_back (expression);
	expression->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"~"))));
	expression->individual_names.push_back (std::wstring (L"a"));
	analyzer_l (expression_top);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());	
	auto routine (result.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	routine->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::node>> arguments;
	arguments.push_back (boost::shared_ptr <lambda_p::core::node> (new lambda_p::core::node));
	(*routine->input) (arguments);
	assert (result.errors->errors.empty ());
	assert (container->results.size () == 1);
	assert (container->results [0] == arguments [0]);
}

void lambda_p_io_test::analyzer::run_12 ()
{
	lambda_p_io_test::analyzer_result result;
	lambda_p_io::analyzer::analyzer analyzer_l (boost::bind (static_cast <void (lambda_p_io_test::analyzer_result::*)(boost::shared_ptr <lambda_p::core::routine>)> (&lambda_p_io_test::analyzer_result::operator()), &result, _1), result.errors);
	auto expression_top (boost::shared_ptr <lambda_p_io::ast::expression> (new lambda_p_io::ast::expression (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> ())));
	expression_top->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L".identity"))));
	expression_top->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"`"))));
	expression_top->values.push_back (boost::shared_ptr <lambda_p_io::ast::identifier> (new lambda_p_io::ast::identifier (std::wstring (L"a"))));
	analyzer_l (expression_top);
	assert (result.routines.size () == 1);
	assert (result.errors->errors.empty ());	
	auto routine (result.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	routine->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::node>> arguments;
	arguments.push_back (boost::shared_ptr <lambda_p::core::node> (new lambda_p::core::node));
	(*routine->input) (arguments);
	assert (result.errors->errors.empty ());
	assert (container->results.size () == 1);
	auto data (boost::dynamic_pointer_cast <lambda_p::core::data> (container->results [0]));
	assert (data.get () != nullptr);
	assert (data->string == std::wstring (L"a"));
}