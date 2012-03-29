#include <mu/script_test/synthesizer/operationd.h>

#include <mu/script/synthesizer/operationd.h>
#include <mu/script/context.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/synthesizer/operationd.h>
#include <mu/core/cluster.h>
#include <mu/io/debugging/mapping.h>
#include <mu/script/cluster/node.h>
#include <mu/io/debugging/node.h>
#include <mu/io/debugging/stream.h>

#include <boost/make_shared.hpp>

void mu::script_test::synthesizer::operationd::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void mu::script_test::synthesizer::operationd::run_1 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.push (boost::make_shared <mu::script::synthesizer::operationd> ());
	context.push (boost::make_shared <mu::core::cluster> ());
	context.push (boost::make_shared <mu::io::debugging::mapping> ());
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 2);
	auto cluster (boost::dynamic_pointer_cast <mu::script::cluster::node> (context.working (0)));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 0);
	auto debugging (boost::dynamic_pointer_cast <mu::io::debugging::mapping> (context.working (1)));
	assert (debugging != nullptr);
	assert (debugging->nodes.size () == 0);
}

void mu::script_test::synthesizer::operationd::run_2 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.push (boost::make_shared <mu::script::synthesizer::operationd> ());
	auto c (boost::make_shared <mu::core::cluster> ());
	context.push (c);
	auto mapping (boost::make_shared <mu::io::debugging::mapping> ());
	context.push (mapping);
	auto c_context (boost::make_shared <mu::io::debugging::node> (mu::io::debugging::context (1, 1, 0, 1, 2, 1)));
	mapping->nodes [c] = c_context;
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 2);
	auto cluster (boost::dynamic_pointer_cast <mu::script::cluster::node> (context.working (0)));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 0);
	auto debugging (boost::dynamic_pointer_cast <mu::io::debugging::mapping> (context.working (1)));
	assert (debugging != nullptr);
	assert (debugging->nodes.size () == 1);
	auto cluster_context (debugging->nodes.find (cluster));
	assert (cluster_context != debugging->nodes.end ());
	assert (cluster_context->second == c_context);
}

void mu::script_test::synthesizer::operationd::run_3 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.push (boost::make_shared <mu::script::synthesizer::operationd> ());
	auto c (boost::make_shared <mu::core::cluster> ());
	context.push (c);
	auto mapping (boost::make_shared <mu::io::debugging::mapping> ());
	context.push (mapping);
	auto c_context (boost::make_shared <mu::io::debugging::node> (mu::io::debugging::context (1, 1, 0, 1, 2, 1)));
	mapping->nodes [c] = c_context;
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 2);
	auto cluster (boost::dynamic_pointer_cast <mu::script::cluster::node> (context.working (0)));
	assert (cluster.get () != nullptr);
	assert (cluster->routines.size () == 0);
	auto debugging (boost::dynamic_pointer_cast <mu::io::debugging::mapping> (context.working (1)));
	assert (debugging != nullptr);
	assert (debugging->nodes.size () == 1);
	auto cluster_context (debugging->nodes.find (cluster));
	assert (cluster_context != debugging->nodes.end ());
	assert (cluster_context->second == c_context);
}