#include <mu/script_test/integer/equal.h>

#include <mu/core/errors/errors.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/integer/equal.h>
#include <mu/script/integer/node.h>
#include <mu/script/bool_c/node.h>
#include <mu/script_runtime/context.h>

#include <boost/make_shared.hpp>

void mu::script_test::integer::equal::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void mu::script_test::integer::equal::run_1 ()
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script_runtime::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::integer::equal> ());
	ctx.push (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (3)));
	ctx.push (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (5)));
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
	auto result (boost::dynamic_pointer_cast <mu::script::bool_c::node> (ctx.working (0)));
	assert (result.get () != nullptr);
	assert (result->value == false);
}

void mu::script_test::integer::equal::run_2 ()
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script_runtime::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::integer::equal> ());
	ctx.push (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (3)));
	ctx.push (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (3)));
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
	auto result (boost::dynamic_pointer_cast <mu::script::bool_c::node> (ctx.working (0)));
	assert (result.get () != nullptr);
	assert (result->value == true);
}

void mu::script_test::integer::equal::run_3 ()
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script_runtime::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::integer::equal> ());
	ctx.push (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (3)));
	ctx.push (boost::shared_ptr <mu::core::node> (new mu::core::node));
	auto valid (ctx ());
	assert (!valid);
}