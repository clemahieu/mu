#include "routine.h"

#include <mu/script/routine.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/call.h>
#include <mu/script/identity/operation.h>
#include <mu/script/constant.h>
#include <mu/script/expression.h>
#include <mu/script/parameters.h>
#include <mu/core/routine.h>
#include <mu/script/remap.h>
#include <mu/script/cluster/node.h>

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
	boost::shared_ptr <mu::core::errors::error_list> errors (new mu::core::errors::error_list);
	mu::script::routine routine (boost::make_shared <mu::script::cluster::node> ());
	routine.calls.push_back (boost::shared_ptr <mu::script::call> (new mu::script::call (0, mu::core::context ())));
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	routine.perform (errors, arguments, results);
	assert (!errors->errors.empty ());
}

void lambda_p_script_test::routine::run_2 ()
{
	boost::shared_ptr <mu::core::errors::error_list> errors (new mu::core::errors::error_list);
	mu::script::routine routine (boost::make_shared <mu::script::cluster::node> ());
	auto call (boost::shared_ptr <mu::script::call> (new mu::script::call (0, mu::core::context ())));
	call->arguments.push_back (boost::shared_ptr <mu::script::constant> (new mu::script::constant (boost::shared_ptr <mu::core::node> (new mu::script::identity::operation))));
	routine.calls.push_back (call);
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	routine.perform (errors, arguments, results);
	assert (errors->errors.empty ());
}

void lambda_p_script_test::routine::run_3 ()
{
	boost::shared_ptr <mu::core::errors::error_list> errors (new mu::core::errors::error_list);
	mu::script::routine routine (boost::make_shared <mu::script::cluster::node> ());
	auto call (boost::shared_ptr <mu::script::call> (new mu::script::call (0, mu::core::context ())));
	call->arguments.push_back (boost::make_shared <mu::script::parameters> ());
	routine.calls.push_back (call);
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	auto node (boost::shared_ptr <mu::core::node> (new mu::core::node));
	arguments.push_back (node);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	routine.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == node);
}

void lambda_p_script_test::routine::run_4 ()
{
	boost::shared_ptr <mu::core::errors::error_list> errors (new mu::core::errors::error_list);
	auto remapping (boost::make_shared <mu::script::cluster::node> ());
	mu::script::routine routine (remapping);
	auto routine1 (boost::make_shared <mu::script::routine> (boost::make_shared <mu::script::cluster::node> ()));
	auto r (boost::make_shared <mu::core::routine> (mu::core::context ()));
	remapping->mapping [r] = routine1;
	auto call (boost::shared_ptr <mu::script::call> (new mu::script::call (0, mu::core::context ())));
	call->arguments.push_back (boost::make_shared <mu::script::remap> (r));
	routine.calls.push_back (call);
	auto call1 (boost::make_shared <mu::script::call> (0, mu::core::context ()));
	call1->arguments.push_back (boost::make_shared <mu::script::constant> (boost::make_shared <mu::script::identity::operation> ()));
	auto id (boost::make_shared <mu::script::identity::operation> ());
	call1->arguments.push_back (boost::make_shared <mu::script::constant> (id));
	routine1->calls.push_back (call1);
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	auto node (boost::shared_ptr <mu::core::node> (new mu::core::node));
	arguments.push_back (node);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	routine.perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == id);
}