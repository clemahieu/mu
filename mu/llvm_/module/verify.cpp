#include "verify.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module/node.h>

#include <llvm/Analysis/Verifier.h>
#include <llvm/Module.h>

void mu::llvm_::module::verify::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::module::node> (context_a.parameters [0]));
	if (one.get () != nullptr)
	{
		std::string error_info;
		auto error (llvm::verifyModule (*one->module, llvm::VerifierFailureAction::ReturnStatusAction, &error_info));
		if (error)
		{
			std::wstring error_info_l (error_info.begin (), error_info.end ());
			(*context_a.errors) (error_info_l);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::module::verify::count ()
{
	return 1;
}

std::wstring mu::llvm_::module::verify::name ()
{
	return std::wstring (L"mu::llvm_::module::verify");
}