#include <mu/script_test/closure/single.h>

#include <mu/core/errors/errors.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/closure/single.h>
#include <mu/script/identity/operation.h>
#include <mu/script_runtime/context.h>

#include <boost/make_shared.hpp>

void mu::script_test::closure::single::run ()
{
	run_1 ();
}

void mu::script_test::closure::single::run_1 ()
{
	std::vector <boost::shared_ptr <mu::core::node>> closed;
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	closed.push_back (n1);
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script_runtime::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::closure::single> (closed, boost::shared_ptr <mu::script_runtime::operation> (new mu::script::identity::operation)));
	auto n2 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	ctx.push (n2);
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 2);
	assert (ctx.working (0) == n1);
	assert (ctx.working (1) == n2);
}