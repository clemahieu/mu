#include <mu/script_test/package/create.h>

#include <mu/core/errors/errors.h>
#include <mu/script/package/create.h>
#include <mu/script/package/node.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

void mu::script_test::package::create::run ()
{
	run_1 ();
}

void mu::script_test::package::create::run_1 ()
{
	mu::core::errors::errors errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::package::create> ());
	auto result (ctx ());
	assert (result);
	assert (ctx.working_size () == 1);
	auto node (boost::dynamic_pointer_cast <mu::script::package::node> (ctx.working (0)));
	assert (node.get () != nullptr);
}