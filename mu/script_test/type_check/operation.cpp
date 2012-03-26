#include <mu/script_test/type_check/operation.h>

#include <mu/core/errors/error_list.h>
#include <mu/script/type_check/operation.h>
#include <mu/script/identity/operation.h>

#include <boost/make_shared.hpp>

void mu::script_test::type_check::operation::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
}

void mu::script_test::type_check::operation::run_1 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::type_check::operation <>> (identity));
	auto valid (ctx ());
	assert (valid);
}

void mu::script_test::type_check::operation::run_2 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::type_check::operation <>> (identity));
	ctx.push (boost::make_shared <mu::script::identity::operation> ());
	auto valid (ctx ());
	assert (!valid);
	assert (ctx.working_size () == 0);
}

void mu::script_test::type_check::operation::run_3 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::type_check::operation <mu::script::identity::operation>> (identity));
	ctx.push (boost::make_shared <mu::script::identity::operation> ());
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
}

void mu::script_test::type_check::operation::run_4 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::type_check::operation <mu::script::identity::operation>> (identity));
	auto valid (ctx ());
	assert (!valid);
	assert (ctx.working_size () == 0);
}

void mu::script_test::type_check::operation::run_5 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::type_check::operation <mu::script::identity::operation>> (identity));
	ctx.push (boost::make_shared <mu::core::node> ());
	auto valid (ctx ());
	assert (!valid);
	assert (ctx.working_size () == 0);
}

void mu::script_test::type_check::operation::run_6 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	auto identity (boost::make_shared <mu::script::identity::operation> ());
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::type_check::operation <mu::core::node, mu::core::node>> (identity));
	ctx.push (boost::make_shared <mu::core::node> ());
	ctx.push (boost::make_shared <mu::core::node> ());
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 2);
}