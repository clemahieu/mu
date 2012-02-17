#include "add_function.h"

#include <lambda_p_llvm/function/node.h>
#include <lambda_p_llvm/module/node.h>

#include <llvm/Module.h>

void lambda_p_llvm::module::add_function::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_llvm::function::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{			
			one->module->getFunctionList ().push_back (two->function ());
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

size_t lambda_p_llvm::module::add_function::count ()
{
	return 2;
}

std::wstring lambda_p_llvm::module::add_function::name ()
{
	return std::wstring (L"lambda_p_llvm::module::add_function");
}