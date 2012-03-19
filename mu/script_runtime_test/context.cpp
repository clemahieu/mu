#include <mu/script_runtime_test/context.h>

#include <mu/script_runtime/context.h>
#include <mu/core/node.h>

#include <boost/make_shared.hpp>

void mu::script_runtime_test::context::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
}

void mu::script_runtime_test::context::run_1 ()
{
	mu::script_runtime::context context;
	assert (context.stack.size () == 3);
	assert (context.frame_begin == 3);
	assert (context.base_begin == 1);
	assert (context.base_end == 3);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 0);
	assert (context.locals_begin () == context.locals_end ());
	assert (context.parameters_begin () == context.parameters_end ());
	assert (context.working_begin () == context.working_end ());
}

void mu::script_runtime_test::context::run_2 ()
{
	mu::script_runtime::context context;
	auto working1 (boost::make_shared <mu::core::node> ());
	context.push (working1);
	assert (context.stack.size () == 4);
	assert (context.frame_begin == 3);
	assert (context.base_begin == 1);
	assert (context.base_end == 3);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 1);
	assert (context.working (0) == working1);
	assert (context.working_begin () != context.working_end ());
	assert (++context.working_begin () == context.working_end ());
	assert (--++context.working_begin () != context.working_end ());
	assert (++--++context.working_begin () == context.working_end ());
}

void mu::script_runtime_test::context::run_3 ()
{
	mu::script_runtime::context context;
	context.push (boost::make_shared <mu::core::node> ());
	context.drop ();
	assert (context.stack.size () == 3);
	assert (context.frame_begin == 3);
	assert (context.base_begin == 1);
	assert (context.base_end == 3);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 0);
}

void mu::script_runtime_test::context::run_4 ()
{
	mu::script_runtime::context context;
	auto local1 (boost::make_shared <mu::core::node> ());
	context.push (local1);
	context.slide ();
	assert (context.stack.size () == 4);
	assert (context.frame_begin == 4);
	assert (context.base_begin == 1);
	assert (context.base_end == 3);
	assert (context.locals_size () == 1);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 0);
	assert (context.locals (0) == local1);
	assert (context.locals_begin () != context.locals_end ());
	assert (++context.locals_begin () == context.locals_end ());
}

void mu::script_runtime_test::context::run_5 ()
{
	mu::script_runtime::context context;
	context.push (boost::make_shared <mu::core::node> ());
	context.enter ();
	assert (context.stack.size () == 6);
	assert (context.frame_begin == 6);
	assert (context.base_begin == 4);
	assert (context.base_end == 6);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 0);
}

void mu::script_runtime_test::context::run_6 ()
{
	mu::script_runtime::context context;
	context.push (boost::make_shared <mu::core::node> ());
	context.enter ();
	context.leave ();
	assert (context.stack.size () == 3);
	assert (context.frame_begin == 3);
	assert (context.base_begin == 1);
	assert (context.base_end == 3);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 0);
}

void mu::script_runtime_test::context::run_7 ()
{
	mu::script_runtime::context context;
	context.push (boost::make_shared <mu::core::node> ());
	auto arg1 (boost::make_shared <mu::core::node> ());
	context.push (arg1);
	context.enter ();
	assert (context.stack.size () == 7);
	assert (context.frame_begin == 7);
	assert (context.base_begin == 4);
	assert (context.base_end == 7);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 1);
	assert (context.working_size () == 0);
	assert (context.parameters (0) == arg1);
	assert (context.parameters_begin () != context.parameters_end ());
	assert (++context.parameters_begin () == context.parameters_end ());
}