#include "synthesizer.h"

#include <lambda_p_script_io/synthesizer.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/routine.h>
#include <lambda_p/expression.h>
#include <lambda_p/reference.h>
#include <lambda_p_script/routine.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <vector>

void lambda_p_script_io_test::synthesizer::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_script_io_test::synthesizer::run_1 ()
{
	lambda_p_script_io::synthesizer synthesizer;
	auto routine (boost::shared_ptr <lambda_p::routine> (new lambda_p::routine));
	routine->body = boost::shared_ptr <lambda_p::expression> (new lambda_p::expression);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	auto errors (boost::make_shared <lambda_p::errors::error_list> ());
	arguments.push_back (routine);
	synthesizer (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto result (boost::dynamic_pointer_cast <lambda_p_script::routine> (results [0]));
	assert (result.get () != nullptr);
	assert (result->calls.size () == 1);
}

void lambda_p_script_io_test::synthesizer::run_2 ()
{
	// [[:~]]
	lambda_p_script_io::synthesizer synthesizer;
	auto routine (boost::shared_ptr <lambda_p::routine> (new lambda_p::routine));
	auto root (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression));
	routine->body = root;
	auto parameters (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression));
	root->dependencies.push_back (parameters);
	parameters->dependencies.push_back (routine->parameters);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	auto errors (boost::make_shared <lambda_p::errors::error_list> ());
	arguments.push_back (routine);
	synthesizer (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto result (boost::dynamic_pointer_cast <lambda_p_script::routine> (results [0]));
	assert (result.get () != nullptr);
	assert (result->calls.size () == 2);
}