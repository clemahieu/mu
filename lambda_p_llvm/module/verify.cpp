#include "verify.h"

#include <mu/core/errors/error_target.h>
#include <lambda_p_llvm/module/node.h>

#include <llvm/Analysis/Verifier.h>
#include <llvm/Module.h>

void lambda_p_llvm::module::verify::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		std::string error_info;
		auto error (llvm::verifyModule (*one->module, llvm::VerifierFailureAction::ReturnStatusAction, &error_info));
		if (error)
		{
			std::wstring error_info_l (error_info.begin (), error_info.end ());
			(*errors_a) (error_info_l);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::module::verify::count ()
{
	return 1;
}

std::wstring lambda_p_llvm::module::verify::name ()
{
	return std::wstring (L"lambda_p_llvm::module::verify");
}