#include "synthesizer.h"

#include <mu/script_io/synthesizer.h>
#include <mu/core/errors/error_list.h>
#include <mu/core/routine.h>
#include <mu/core/cluster.h>
#include <mu/core/expression.h>
#include <mu/core/reference.h>
#include <mu/core/parameters.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/cluster/node.h>
#include <mu/script/runtime/call.h>
#include <mu/script/runtime/constant.h>
#include <mu/script/context.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <vector>

void mu::script_io_test::synthesizer::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void mu::script_io_test::synthesizer::run_1 ()
{
	mu::script_io::synthesizer synthesizer;
	auto routine (boost::shared_ptr <mu::core::routine> (new mu::core::routine (mu::core::context (1, 1, 0, 1, 1, 0))));
	routine->body = boost::shared_ptr <mu::core::expression> (new mu::core::expression (mu::core::context (1, 1, 0, 1, 2, 1)));
	auto cluster (boost::make_shared <mu::core::cluster> ());
	cluster->routines.push_back (routine);
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	arguments.push_back (cluster);
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	synthesizer (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto cl (boost::dynamic_pointer_cast <mu::script::cluster::node> (results [0]));
	assert (cl.get () != nullptr);
	assert (cl->routines.size () == 1);
	auto result (boost::dynamic_pointer_cast <mu::script::runtime::routine> (cl->routines [0]));
	assert (result.get () != nullptr);
	assert (result->calls.size () == 1);
}

void mu::script_io_test::synthesizer::run_2 ()
{
	// [[:~]]
	mu::script_io::synthesizer synthesizer;
	auto routine (boost::shared_ptr <mu::core::routine> (new mu::core::routine (mu::core::context (1, 1, 0, 1, 1, 0))));
	auto root (boost::shared_ptr <mu::core::expression> (new mu::core::expression (mu::core::context (1, 1, 0, 1, 6, 5))));
	routine->body = root;
	auto parameters (boost::shared_ptr <mu::core::expression> (new mu::core::expression (mu::core::context (1, 2, 1, 1, 3, 2))));
	root->dependencies.push_back (parameters);
	parameters->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	auto cluster (boost::make_shared <mu::core::cluster> ());
	cluster->routines.push_back (routine);
	arguments.push_back (cluster);
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	synthesizer (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto cl (boost::dynamic_pointer_cast <mu::script::cluster::node> (results [0]));
	assert (cl.get () != nullptr);
	assert (cl->routines.size () == 1);
	auto result (boost::dynamic_pointer_cast <mu::script::runtime::routine> (cl->routines [0]));
	assert (result.get () != nullptr);
	assert (result->calls.size () == 2);
}

void mu::script_io_test::synthesizer::run_3 ()
{
	//[a][;;a]
	mu::script_io::synthesizer synthesizer;
	auto routine1 (boost::make_shared <mu::core::routine> (boost::make_shared <mu::core::expression> (mu::core::context ())));
	auto routine2 (boost::make_shared <mu::core::routine> (boost::make_shared <mu::core::expression> (mu::core::context ())));
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	auto cluster (boost::make_shared <mu::core::cluster> ());
	cluster->routines.push_back (routine1);
	cluster->routines.push_back (routine2);
	routine1->body->dependencies.push_back (routine2);
	arguments.push_back (cluster);
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	synthesizer (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto cl (boost::dynamic_pointer_cast <mu::script::cluster::node> (results [0]));
	assert (cl.get () != nullptr);
	assert (cl->routines.size () == 2);
	auto result1 (boost::dynamic_pointer_cast <mu::script::runtime::routine> (cl->routines [0]));
	auto result2 (boost::dynamic_pointer_cast <mu::script::runtime::routine> (cl->routines [1]));
	assert (result1->calls.size () == 1);
	auto call (result1->calls [0]);
	assert (call->arguments.size () == 1);
	auto argument (boost::dynamic_pointer_cast <mu::script::runtime::constant> (call->arguments [0]));
	assert (argument.get () != nullptr);
	auto rout (boost::dynamic_pointer_cast <mu::script::runtime::routine> (argument->value));
	assert (rout == result2);
}

void mu::script_io_test::synthesizer::run_4 ()
{
	//[a;;a]
	mu::script_io::synthesizer synthesizer;
	auto routine1 (boost::make_shared <mu::core::routine> (boost::make_shared <mu::core::expression> (mu::core::context ())));
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	auto cluster (boost::make_shared <mu::core::cluster> ());
	cluster->routines.push_back (routine1);
	routine1->body->dependencies.push_back (routine1);
	arguments.push_back (cluster);
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	synthesizer (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto cl (boost::dynamic_pointer_cast <mu::script::cluster::node> (results [0]));
	assert (cl.get () != nullptr);
	assert (cl->routines.size () == 1);
	auto result1 (boost::dynamic_pointer_cast <mu::script::runtime::routine> (cl->routines [0]));
	assert (result1->calls.size () == 1);
	auto call (result1->calls [0]);
	assert (call->arguments.size () == 1);
	auto argument (boost::dynamic_pointer_cast <mu::script::runtime::constant> (call->arguments [0]));
	assert (argument.get () != nullptr);
	auto rout (boost::dynamic_pointer_cast <mu::script::runtime::routine> (argument->value));
	assert (rout == result1);
}