#include "routine.h"

#include <mu/script/runtime/routine.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/runtime/call.h>
#include <mu/script/identity/operation.h>
#include <mu/script/runtime/constant.h>
#include <mu/script/runtime/expression.h>
#include <mu/script/runtime/parameters.h>
#include <mu/core/routine.h>
#include <mu/script/cluster/node.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

void mu::script_test::routine::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void mu::script_test::routine::run_1 ()
{
	boost::shared_ptr <mu::core::errors::error_list> errors (new mu::core::errors::error_list);
	mu::script::runtime::routine routine;
	routine.calls.push_back (boost::shared_ptr <mu::script::runtime::call> (new mu::script::runtime::call (0)));
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	routine (ctx);
	assert (!errors->errors.empty ());
}

void mu::script_test::routine::run_2 ()
{
	boost::shared_ptr <mu::core::errors::error_list> errors (new mu::core::errors::error_list);
	mu::script::runtime::routine routine;
	auto call (boost::shared_ptr <mu::script::runtime::call> (new mu::script::runtime::call (0)));
	call->arguments.push_back (boost::shared_ptr <mu::script::runtime::constant> (new mu::script::runtime::constant (boost::shared_ptr <mu::core::node> (new mu::script::identity::operation))));
	routine.calls.push_back (call);
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	routine (ctx);
	assert (errors->errors.empty ());
}

void mu::script_test::routine::run_3 ()
{
	boost::shared_ptr <mu::core::errors::error_list> errors (new mu::core::errors::error_list);
	mu::script::runtime::routine routine;
	auto call (boost::shared_ptr <mu::script::runtime::call> (new mu::script::runtime::call (0)));
	call->arguments.push_back (boost::make_shared <mu::script::runtime::parameters> ());
	routine.calls.push_back (call);
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	auto node (boost::shared_ptr <mu::core::node> (new mu::core::node));
	arguments.push_back (node);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	routine (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == node);
}

void mu::script_test::routine::run_4 ()
{
	boost::shared_ptr <mu::core::errors::error_list> errors (new mu::core::errors::error_list);
	auto remapping (boost::make_shared <mu::script::cluster::node> ());
	mu::script::runtime::routine routine;
	auto routine1 (boost::make_shared <mu::script::runtime::routine> ());
	auto r (boost::make_shared <mu::core::routine> ());
	auto call (boost::shared_ptr <mu::script::runtime::call> (new mu::script::runtime::call (0)));
	call->arguments.push_back (boost::make_shared <mu::script::runtime::constant> (routine1));
	routine.calls.push_back (call);
	auto call1 (boost::make_shared <mu::script::runtime::call> (0));
	call1->arguments.push_back (boost::make_shared <mu::script::runtime::constant> (boost::make_shared <mu::script::identity::operation> ()));
	auto id (boost::make_shared <mu::script::identity::operation> ());
	call1->arguments.push_back (boost::make_shared <mu::script::runtime::constant> (id));
	routine1->calls.push_back (call1);
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	auto node (boost::shared_ptr <mu::core::node> (new mu::core::node));
	arguments.push_back (node);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	routine (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == id);
}