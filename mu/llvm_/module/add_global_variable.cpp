#include "add_global_variable.h"

#include <mu/llvm_/global_variable/node.h>
#include <mu/llvm_/module/node.h>

#include <llvm/Module.h>

void mu::llvm_::module::add_global_variable::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::module::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::global_variable::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			one->module->getGlobalList ().push_back (two->global_variable ());
		}
		else
		{
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::llvm_::module::add_global_variable::count ()
{
	return 2;
}