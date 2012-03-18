#include <mu/script_runtime_test/context.h>

#include <mu/script_runtime/context.h>
#include <mu/core/node.h>

#include <boost/make_shared.hpp>

void mu::script_runtime_test::context::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void mu::script_runtime_test::context::run_1 ()
{
	mu::script_runtime::context context;
	assert (context.stack.size () == 0);
	assert (context.working_begin == 0);
	assert (context.base_begin == 0);
	assert (context.base_end == 0);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 0);
}

void mu::script_runtime_test::context::run_2 ()
{
	mu::script_runtime::context context;
	context.push (boost::make_shared <mu::core::node> ());
	assert (context.stack.size () == 1);
	assert (context.working_begin == 0);
	assert (context.base_begin == 0);
	assert (context.base_end == 0);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 1);
}

void mu::script_runtime_test::context::run_3 ()
{
	mu::script_runtime::context context;
	context.push (boost::make_shared <mu::core::node> ());
	context.drop ();
	assert (context.stack.size () == 0);
	assert (context.working_begin == 0);
	assert (context.base_begin == 0);
	assert (context.base_end == 0);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 0);
}