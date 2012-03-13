#include "routine.h"

#include <mu/script_io/routine.h>
#include <mu/core/expression.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/runtime/reference.h>
#include <mu/script/runtime/expression.h>
#include <mu/script/runtime/constant.h>
#include <mu/script/runtime/call.h>
#include <mu/script/runtime/parameters.h>
#include <mu/core/parameters.h>
#include <mu/core/routine.h>
#include <mu/script/cluster/node.h>
#include <mu/script_io/cluster.h>
#include <mu/core/cluster.h>

#include <boost/make_shared.hpp>

void mu::script_io_test::routine::run ()
{
	run_1 ();
}

void mu::script_io_test::routine::run_1 ()
{
	std::vector <boost::shared_ptr <mu::core::expression>> calls;
	auto call1 (boost::shared_ptr <mu::core::expression> (new mu::core::expression));
	calls.push_back (call1);
	call1->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	auto call2 (boost::shared_ptr <mu::core::expression> (new mu::core::expression));
	call2->dependencies.push_back (call1);
	calls.push_back (call2);
	auto rout (boost::make_shared <mu::core::routine> (call2));
	mu::script_io::cluster cluster (boost::make_shared <mu::core::cluster> ());
	auto routine (boost::make_shared <mu::script::runtime::routine> ());
	mu::script_io::routine r (cluster, rout, routine);
	assert (routine->calls.size () == 2);
	auto c1 (routine->calls [0]);
	assert (c1->results == 0);
	assert (c1->arguments.size () == 1);
	auto a1 (boost::dynamic_pointer_cast <mu::script::runtime::parameters> (c1->arguments [0]));
	assert (a1.get () != nullptr);
	auto c2 (routine->calls [1]);
	assert (c2->results == 1);
	assert (c2->arguments.size () == 1);
	auto a2 (boost::dynamic_pointer_cast <mu::script::runtime::expression> (c2->arguments [0]));
	assert (a2.get () != nullptr);
	assert (a2->index == 0);
}