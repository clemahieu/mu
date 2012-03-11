#include "create.h"

#include <mu/script/package/create.h>
#include <mu/script/package/node.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>

void mu::script_test::package::create::run ()
{
	run_1 ();
}

void mu::script_test::package::create::run_1 ()
{
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	mu::script::package::create create;
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	std::vector <std::type_info const *> stack;
	std::vector <mu::core::context> context_stack;
    auto ctx (mu::script::context (errors, arguments, results, stack, context_stack));
	create (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto node (boost::dynamic_pointer_cast <mu::script::package::node> (results [0]));
	assert (node.get () != nullptr);
}