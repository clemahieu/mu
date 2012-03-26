#include <mu/script_test/frame.h>

#include <mu/script/context.h>
#include <mu/script/frame.h>
#include <mu/core/node.h>

#include <boost/make_shared.hpp>

void mu::script_test::frame::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void mu::script_test::frame::run_1 ()
{
	mu::script::context context;
	assert (context.stack.size () == 2);
	{
		mu::script::frame frame (context);
	}
	assert (context.stack.size () == 2);
}

void mu::script_test::frame::run_2 ()
{
	mu::script::context context;
	assert (context.stack.size () == 2);
	{
		mu::script::frame frame (context);
		assert (context.stack.size () == 3);
		context.push (boost::make_shared <mu::core::node> ());
		assert (context.stack.size () == 4);
	}
	assert (context.stack.size () == 2);
}

void mu::script_test::frame::run_3 ()
{
	mu::script::context context;
	assert (context.stack.size () == 2);
	context.push (boost::make_shared <mu::core::node> ());
	assert (context.stack.size () == 3);
	{
		mu::script::frame frame (context);
		assert (context.stack.size () == 4);
		context.push (boost::make_shared <mu::core::node> ());
		assert (context.stack.size () == 5);
	}
	assert (context.stack.size () == 3);
}