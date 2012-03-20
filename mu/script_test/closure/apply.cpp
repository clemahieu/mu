#include <mu/script_test/closure/apply.h>

#include <mu/core/errors/error_list.h>
#include <mu/core/errors/errors.h>
#include <mu/script/closure/operation.h>
#include <mu/script/closure/apply.h>
#include <mu/script/identity/operation.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

void mu::script_test::closure::apply::run ()
{
	run_1 ();
}

void mu::script_test::closure::apply::run_1 ()
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	auto c1 (boost::shared_ptr <mu::core::node> (new mu::script::closure::operation (1, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation))));
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	arguments.push_back (c1);
	arguments.push_back (n1);
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::apply> ());
	auto result (ctx ());
	assert (result);
	assert (ctx.working_size () == 1);
	auto c2 (boost::dynamic_pointer_cast <mu::script::closure::operation> (ctx.working (0)));
	assert (c2.get () != nullptr);
	ctx.drop ();
	ctx.push (c2);
	auto result2 (ctx ());
	assert (result2);
	assert (ctx.working_size () == 1);
	assert (ctx.working (0) == n1);
}