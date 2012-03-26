#include <mu/script_test/closure/operation.h>

#include <mu/script/closure/operation.h>
#include <mu/script/identity/operation.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/closure/hole.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

void mu::script_test::closure::operation::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
}

void mu::script_test::closure::operation::run_1 ()
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::operation> (0, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation)));
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 0);
}

void mu::script_test::closure::operation::run_2 ()
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::operation> (1, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation)));
	auto node (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (node);
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
	assert (ctx.working (0) == node);
}

void mu::script_test::closure::operation::run_3 ()
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::operation> (2, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation)));
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n1);
	auto n2 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n2);
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 2);
	assert (ctx.working (0) == n1);
	assert (ctx.working (1) == n2);
}

void mu::script_test::closure::operation::run_4 ()
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::operation> (2, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation)));
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n1);
	auto n2 (boost::shared_ptr <mu::core::node> (new mu::script::closure::hole));
	ctx.push (n2);
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
	auto result (boost::dynamic_pointer_cast <mu::script::closure::operation> (ctx.working (0)));
	assert (result.get () != nullptr);
	ctx.drop ();
	ctx.push (result);
	auto n3 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n3);
	auto valid2 (ctx ());
	assert (valid2);
	assert (ctx.working_size () == 2);
	assert (ctx.working (0) == n1);
	assert (ctx.working (1) == n3);
}

void mu::script_test::closure::operation::run_5 ()
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::operation> (2, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation)));
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::script::closure::hole));
	ctx.push (n1);
	auto n2 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n2);
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
	auto result (boost::dynamic_pointer_cast <mu::script::closure::operation> (ctx.working (0)));
	assert (result.get () != nullptr);
	ctx.drop ();
	ctx.push (result);
	auto n3 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n3);
	auto valid2 (ctx ());
	assert (valid2);
	assert (ctx.working_size () == 2);
	assert (ctx.working (0) == n3);
	assert (ctx.working (1) == n2);
}