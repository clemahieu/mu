#include <mu/llvm_/module_verify.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Analysis/Verifier.h>
#include <llvm/Module.h>

bool mu::llvm_::module::verify::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::llvm_::module::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::module::node *> (context_a.parameters (0)));
		std::string error_info;
		auto error (llvm::verifyModule (*one->module, llvm::VerifierFailureAction::ReturnStatusAction, &error_info));
		if (error)
		{
			mu::string error_info_l (error_info.begin (), error_info.end ());
			context_a.errors (error_info_l);
			valid = false;
		}
	}
	return valid;
}

mu::string mu::llvm_::module::verify::name ()
{
	return mu::string (U"mu::llvm_::module::verify");
}