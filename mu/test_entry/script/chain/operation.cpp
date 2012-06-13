#include <mu/core/errors/error_list.h>
#include <mu/script/chain/operation.h>
#include <mu/test_entry/script/chain/ten_count.h>
#include <mu/script/integer/node.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

TEST (script_test, chain_operation1)
{
	auto operation (boost::shared_ptr <mu::core::node> (new mu::script_test::chain::ten_count));
	auto count (boost::shared_ptr <mu::script::integer::node> (new mu::script::integer::node (50)));
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::chain::operation> ());
	ctx.push (operation);
	ctx.push (count);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto result (boost::dynamic_pointer_cast <mu::script::integer::node> (ctx.working (0)));
	EXPECT_EQ (result->value, 40);
}