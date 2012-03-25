#include <mu/script_test/cluster/remap.h>

#include <mu/script/cluster/remap.h>
#include <mu/script/context.h>
#include <mu/core/cluster.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>
#include <mu/script/identity/operation.h>
#include <mu/script/fail/operation.h>
#include <mu/core/errors/error_list.h>

#include <boost/make_shared.hpp>

void mu::script_test::cluster::remap::run ()
{
	run_1 ();
}

void mu::script_test::cluster::remap::run_1 ()
{
	auto cluster (boost::make_shared <mu::core::cluster> ());
	auto routine (boost::make_shared <mu::core::routine> ());
	cluster->routines.push_back (routine);
	auto body (boost::make_shared <mu::core::expression> ());
	routine->body = body;
	auto fail (boost::make_shared <mu::script::fail::operation> ());
	body->dependencies.push_back (fail);
	auto remap (boost::make_shared <mu::script::cluster::remap> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	remap->mapping [fail] = identity;
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.push (remap);
	context.push (cluster);
	auto valid (context ());
	assert (context.working_size () == 1);
	auto cl (boost::dynamic_pointer_cast <mu::core::cluster> (context.working (0)));
	assert (cl.get () != nullptr);
	assert (cl->routines.size () == 1);
	assert (cl->routines [0]->body->dependencies.size () == 1);
	assert (cl->routines [0]->body->dependencies [0] == identity);
}