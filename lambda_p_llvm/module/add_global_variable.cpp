#include "add_global_variable.h"

#include <lambda_p_llvm/global_variable/node.h>
#include <lambda_p_llvm/module/node.h>

#include <llvm/Module.h>

void lambda_p_llvm::module::add_global_variable::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_llvm::global_variable::node> (parameters [1]));
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

size_t lambda_p_llvm::module::add_global_variable::count ()
{
	return 2;
}