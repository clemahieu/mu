#include "routine.h"

#include <lambda_p_script/routine.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_script/call.h>
#include <lambda_p_script/identity/operation.h>
#include <lambda_p_script/constant.h>
#include <lambda_p_script/expression.h>
#include <lambda_p_script/parameters.h>
#include <lambda_p_script/remapping.h>
#include <lambda_p/routine.h>
#include <lambda_p_script/remap.h>

#include <boost/make_shared.hpp>

void lambda_p_script_test::routine::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_script_test::routine::run_1 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	lambda_p_script::routine routine (boost::make_shared <lambda_p_script::remapping> ());
	routine.calls.push_back (boost::shared_ptr <lambda_p_script::call> (new lambda_p_script::call (0, lambda_p::context ())));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine.perform (errors, arguments, results);
	assert (!errors->errors.empty ());
}

void lambda_p_script_test::routine::run_2 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	lambda_p_script::routine routine (boost::make_shared <lambda_p_script::remapping> ());
	auto call (boost::shared_ptr <lambda_p_script::call> (new lambda_p_script::call (0, lambda_p::context ())));
	call->arguments.push_back (boost::shared_ptr <lambda_p_script::constant> (new lambda_p_script::constant (boost::shared_ptr <lambda_p::node> (new lambda_p_script::identity::operation))));
	routine.calls.push_back (call);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine.perform (errors, arguments, results);
	assert (errors->errors.empty ());
}

void lambda_p_script_test::routine::run_3 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	lambda_p_script::routine routine (boost::make_shared <lambda_p_script::remapping> ());
	auto call (boost::shared_ptr <lambda_p_script::call> (new lambda_p_script::call (0, lambda_p::context ())));
	call->arguments.push_back (boost::make_shared <lambda_p_script::parameters> ());
	routine.calls.push_back (call);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto node (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (node);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == node);
}

void lambda_p_script_test::routine::run_4 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	auto remapping (boost::make_shared <lambda_p_script::remapping> ());
	lambda_p_script::routine routine (remapping);
	auto routine1 (boost::make_shared <lambda_p_script::routine> (boost::make_shared <lambda_p_script::remapping> ()));
	auto r (boost::make_shared <lambda_p::routine> (lambda_p::context ()));
	remapping->generated [r] = routine1;
	auto call (boost::shared_ptr <lambda_p_script::call> (new lambda_p_script::call (0, lambda_p::context ())));
	call->arguments.push_back (boost::make_shared <lambda_p_script::remap> (r));
	routine.calls.push_back (call);
	auto call1 (boost::make_shared <lambda_p_script::call> (0, lambda_p::context ()));
	call1->arguments.push_back (boost::make_shared <lambda_p_script::constant> (boost::make_shared <lambda_p_script::identity::operation> ()));
	auto id (boost::make_shared <lambda_p_script::identity::operation> ());
	call1->arguments.push_back (boost::make_shared <lambda_p_script::constant> (id));
	routine1->calls.push_back (call1);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	auto node (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	arguments.push_back (node);
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	routine.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == id);
}