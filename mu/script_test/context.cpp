#include <mu/script_test/context.h>

#include <mu/script/context.h>
#include <mu/core/node.h>
#include <mu/script/identity/operation.h>

#include <boost/make_shared.hpp>

void mu::script_test::context::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
	run_8 ();
	run_9 ();
	run_10 ();
	run_11 ();
	run_12 ();
	run_13 ();
}

void mu::script_test::context::run_1 ()
{
	mu::script::context context;
	assert (context.stack.size () == 2);
	assert (context.frame_begin == 2);
	assert (context.base_begin == 0);
	assert (context.base_end == 2);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 0);
	assert (context.locals_begin () == context.locals_end ());
	assert (context.parameters_begin () == context.parameters_end ());
	assert (context.working_begin () == context.working_end ());
}

void mu::script_test::context::run_2 ()
{
	mu::script::context context;
	auto working1 (boost::make_shared <mu::core::node> ());
	context.push (working1);
	assert (context.stack.size () == 3);
	assert (context.frame_begin == 2);
	assert (context.base_begin == 0);
	assert (context.base_end == 2);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 1);
	assert (context.working (0) == working1);
	assert (context.working_begin () != context.working_end ());
	assert (++context.working_begin () == context.working_end ());
	assert (--++context.working_begin () != context.working_end ());
	assert (++--++context.working_begin () == context.working_end ());
}

void mu::script_test::context::run_3 ()
{
	mu::script::context context;
	context.push (boost::make_shared <mu::core::node> ());
	context.drop ();
	assert (context.stack.size () == 2);
	assert (context.frame_begin == 2);
	assert (context.base_begin == 0);
	assert (context.base_end == 2);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 0);
}

void mu::script_test::context::run_4 ()
{
	mu::script::context context;
	auto local1 (boost::make_shared <mu::core::node> ());
	context.push (local1);
	context.slide ();
	assert (context.stack.size () == 3);
	assert (context.frame_begin == 3);
	assert (context.base_begin == 0);
	assert (context.base_end == 2);
	assert (context.locals_size () == 1);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 0);
	assert (context.locals (0) == local1);
	assert (context.locals_begin () != context.locals_end ());
	assert (++context.locals_begin () == context.locals_end ());
}

void mu::script_test::context::run_5 ()
{
	mu::script::context context;
	context.enter ();
	assert (context.stack.size () == 4);
	assert (context.frame_begin == 4);
	assert (context.base_begin == 2);
	assert (context.base_end == 4);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 0);
}

void mu::script_test::context::run_6 ()
{
	mu::script::context context;
	context.enter ();
	context.leave ();
	assert (context.stack.size () == 2);
	assert (context.frame_begin == 2);
	assert (context.base_begin == 0);
	assert (context.base_end == 2);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 0);
}

void mu::script_test::context::run_7 ()
{
	mu::script::context context;
	auto arg1 (boost::make_shared <mu::core::node> ());
	context.push (arg1);
	context.enter ();
	assert (context.stack.size () == 5);
	assert (context.frame_begin == 5);
	assert (context.base_begin == 2);
	assert (context.base_end == 5);
	assert (context.locals_size () == 0);
	assert (context.parameters_size () == 1);
	assert (context.working_size () == 0);
	assert (context.parameters (0) == arg1);
	assert (context.parameters_begin () != context.parameters_end ());
	assert (++context.parameters_begin () == context.parameters_end ());
}

void mu::script_test::context::run_8 ()
{
	mu::script::context context;
	auto arg1 (boost::make_shared <mu::core::node> ());
	context.push (arg1);
	context.enter ();
	auto res1 (boost::make_shared <mu::core::node> ());
	context.push (res1);
	assert (context.working_size () == 1);
	assert (*context.working_begin () == res1);
	context.leave ();
	assert (context.working_size () == 1);
	assert (*context.working_begin () == res1);
}

void mu::script_test::context::run_9 ()
{
	mu::script::context context;
	auto arg1 (boost::make_shared <mu::script::identity::operation> ());
	context.push (arg1);
	auto arg2 (boost::make_shared <mu::script::identity::operation> ());
	context.push (arg2);
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 1);
	assert (context.working (0) == arg2);
}

void mu::script_test::context::run_10 ()
{
	mu::script::context context;
	auto valid (context ());
	assert (!valid);
	assert (context.working_size () == 0);
}

void mu::script_test::context::run_11 ()
{
	mu::script::context context;
	auto arg1 (boost::make_shared <mu::core::node> ());
	context.push (arg1);
	auto arg2 (boost::make_shared <mu::script::identity::operation> ());
	context.push (arg2);
	auto valid (context ());
	assert (!valid);
	assert (context.working_size () == 0);
}

void mu::script_test::context::run_12 ()
{
	mu::script::context context;
	context.reserve (1);
	assert (context.stack.size () == 3);
	assert (context.frame_begin == 3);
	assert (context.base_begin == 0);
	assert (context.base_end == 2);
	assert (context.locals_size () == 1);
	assert (context.parameters_size () == 0);
	assert (context.working_size () == 0);
}

void mu::script_test::context::run_13 ()
{
	mu::script::context context;
	context.reserve (1);
	auto val1 (boost::make_shared <mu::core::node> ());
	context.push (val1);
	context.assign (context.locals_begin (), context.working_begin (), context.working_end ());
	assert (context.locals (0) == context.working (0));
}