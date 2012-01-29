#include "synthesizer.h"

#include <lambda_p_script_io/synthesizer.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/routine.h>
#include <lambda_p/cluster.h>
#include <lambda_p/expression.h>
#include <lambda_p/reference.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script/cluster.h>
#include <lambda_p_script/call.h>
#include <lambda_p_script/constant.h>
#include <lambda_p/link.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <vector>

void lambda_p_script_io_test::synthesizer::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_script_io_test::synthesizer::run_1 ()
{
	lambda_p_script_io::synthesizer synthesizer;
	auto routine (boost::shared_ptr <lambda_p::routine> (new lambda_p::routine (lambda_p::context (1, 1, 0, 1, 1, 0))));
	routine->body = boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (lambda_p::context (1, 1, 0, 1, 2, 1)));
	auto cluster (boost::make_shared <lambda_p::cluster> ());
	cluster->routines.push_back (routine);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	auto errors (boost::make_shared <lambda_p::errors::error_list> ());
	arguments.push_back (cluster);
	synthesizer (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto cl (boost::dynamic_pointer_cast <lambda_p_script::cluster> (results [0]));
	assert (cl.get () != nullptr);
	assert (cl->routines.size () == 1);
	auto result (boost::dynamic_pointer_cast <lambda_p_script::routine> (cl->routines [0]));
	assert (result.get () != nullptr);
	assert (result->calls.size () == 1);
}

void lambda_p_script_io_test::synthesizer::run_2 ()
{
	// [[:~]]
	lambda_p_script_io::synthesizer synthesizer;
	auto routine (boost::shared_ptr <lambda_p::routine> (new lambda_p::routine (lambda_p::context (1, 1, 0, 1, 1, 0))));
	auto root (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (lambda_p::context (1, 1, 0, 1, 6, 5))));
	routine->body = root;
	auto parameters (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (lambda_p::context (1, 2, 1, 1, 3, 2))));
	root->dependencies.push_back (parameters);
	parameters->dependencies.push_back (routine->parameters);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	auto errors (boost::make_shared <lambda_p::errors::error_list> ());
	auto cluster (boost::make_shared <lambda_p::cluster> ());
	cluster->routines.push_back (routine);
	arguments.push_back (cluster);
	synthesizer (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto cl (boost::dynamic_pointer_cast <lambda_p_script::cluster> (results [0]));
	assert (cl.get () != nullptr);
	assert (cl->routines.size () == 1);
	auto result (boost::dynamic_pointer_cast <lambda_p_script::routine> (cl->routines [0]));
	assert (result.get () != nullptr);
	assert (result->calls.size () == 2);
}

void lambda_p_script_io_test::synthesizer::run_3 ()
{
	//[a][;;a]
	lambda_p_script_io::synthesizer synthesizer;
	auto routine1 (boost::make_shared <lambda_p::routine> (boost::make_shared <lambda_p::expression> (lambda_p::context ()), boost::make_shared <lambda_p::expression> (lambda_p::context ())));
	auto routine2 (boost::make_shared <lambda_p::routine> (boost::make_shared <lambda_p::expression> (lambda_p::context ()), boost::make_shared <lambda_p::expression> (lambda_p::context ())));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	auto errors (boost::make_shared <lambda_p::errors::error_list> ());
	auto cluster (boost::make_shared <lambda_p::cluster> ());
	cluster->routines.push_back (routine1);
	cluster->routines.push_back (routine2);
	routine1->body->dependencies.push_back (boost::make_shared <lambda_p::link> (cluster, 1));
	arguments.push_back (cluster);
	synthesizer (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto cl (boost::dynamic_pointer_cast <lambda_p_script::cluster> (results [0]));
	assert (cl.get () != nullptr);
	assert (cl->routines.size () == 2);
	auto result1 (boost::dynamic_pointer_cast <lambda_p_script::routine> (cl->routines [0]));
	auto result2 (boost::dynamic_pointer_cast <lambda_p_script::routine> (cl->routines [1]));
	assert (result1->calls.size () == 1);
	auto call (result1->calls [0]);
	assert (call->arguments.size () == 1);
	auto argument (boost::dynamic_pointer_cast <lambda_p_script::constant> (call->arguments [0]));
	assert (argument.get () != nullptr);
	auto rout (boost::dynamic_pointer_cast <lambda_p_script::routine> (argument->value));
	assert (rout == result2);
}

void lambda_p_script_io_test::synthesizer::run_4 ()
{
	//[a;;a]
	lambda_p_script_io::synthesizer synthesizer;
	auto routine1 (boost::make_shared <lambda_p::routine> (boost::make_shared <lambda_p::expression> (lambda_p::context ()), boost::make_shared <lambda_p::expression> (lambda_p::context ())));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	auto errors (boost::make_shared <lambda_p::errors::error_list> ());
	auto cluster (boost::make_shared <lambda_p::cluster> ());
	cluster->routines.push_back (routine1);
	routine1->body->dependencies.push_back (boost::make_shared <lambda_p::link> (cluster, 0));
	arguments.push_back (cluster);
	synthesizer (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto cl (boost::dynamic_pointer_cast <lambda_p_script::cluster> (results [0]));
	assert (cl.get () != nullptr);
	assert (cl->routines.size () == 1);
	auto result1 (boost::dynamic_pointer_cast <lambda_p_script::routine> (cl->routines [0]));
	assert (result1->calls.size () == 1);
	auto call (result1->calls [0]);
	assert (call->arguments.size () == 1);
	auto argument (boost::dynamic_pointer_cast <lambda_p_script::constant> (call->arguments [0]));
	assert (argument.get () != nullptr);
	auto rout (boost::dynamic_pointer_cast <lambda_p_script::routine> (argument->value));
	assert (rout == result1);
}