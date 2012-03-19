#include <mu/script_test/chain/operation.h>

#include <mu/core/errors/error_list.h>
#include <mu/script/chain/operation.h>
#include <mu/script_test/chain/ten_count.h>
#include <mu/script/integer/node.h>
#include <mu/script_runtime/context.h>

#include <boost/make_shared.hpp>

void mu::script_test::chain::operation::run ()
{
	run_1 ();
}

void mu::script_test::chain::operation::run_1 ()
{
	auto operation (boost::shared_ptr <mu::core::node> (new mu::script_test::chain::ten_count));
	auto count (boost::shared_ptr <mu::script::integer::node> (new mu::script::integer::node (50)));
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script_runtime::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::chain::operation> ());
	ctx.push (operation);
	ctx.push (count);
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
	auto result (boost::dynamic_pointer_cast <mu::script::integer::node> (ctx.working (0)));
	assert (result->value == 40);
}