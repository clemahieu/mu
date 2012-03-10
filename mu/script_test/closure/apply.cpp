#include "apply.h"

#include <mu/core/errors/error_list.h>
#include <mu/script/closure/operation.h>
#include <mu/script/closure/apply.h>
#include <mu/script/identity/operation.h>
#include <mu/script/context.h>

void mu::script_test::closure::apply::run ()
{
	run_1 ();
}

void mu::script_test::closure::apply::run_1 ()
{
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	auto c1 (boost::shared_ptr <mu::core::node> (new mu::script::closure::operation (1, boost::shared_ptr <mu::script::operation> (new mu::script::identity::operation))));
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	arguments.push_back (c1);
	arguments.push_back (n1);
	std::vector <boost::shared_ptr <mu::core::node>> results;
	mu::script::closure::apply apply;
	std::vector <std::type_info const *> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	apply (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto c2 (boost::dynamic_pointer_cast <mu::script::closure::operation> (results [0]));
	assert (c2.get () != nullptr);	
	std::vector <boost::shared_ptr <mu::core::node>> a2;
	std::vector <boost::shared_ptr <mu::core::node>> r2;
	std::vector <std::type_info const *> stack2;
    auto ctx2 (mu::script::context (errors, a2, r2, stack2));
	(*c2) (ctx2);
	assert (errors->errors.empty ());
	assert (r2.size () == 1);
	assert (r2 [0] == n1);
}