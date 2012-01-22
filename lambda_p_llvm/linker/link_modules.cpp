#include "link_modules.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/module/node.h>

#include <llvm/Linker.h>

void lambda_p_llvm::linker::link_modules::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			std::string message;
			bool result (llvm::Linker::LinkModules (one->module, two->module, llvm::Linker::DestroySource, &message));
			if (result)
			{
				std::wstring message_l (message.begin (), message.end ());
				(*errors_a) (message_l);
			}
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

size_t lambda_p_llvm::linker::link_modules::count ()
{
	return 2;
}

std::wstring lambda_p_llvm::linker::link_modules::name ()
{
	return std::wstring (L"lambda_p_llvm::linker::link_modules");
}