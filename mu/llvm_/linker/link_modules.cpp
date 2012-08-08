#include <mu/llvm_/linker/link_modules.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module/node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Linker.h>

#include <gc_cpp.h>

bool mu::llvm_::linker::link_modules::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::llvm_::module::node, mu::llvm_::module::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::module::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::module::node *> (context_a.parameters (1)));
		std::string message;
		bool result (llvm::Linker::LinkModules (one->module, two->module, llvm::Linker::DestroySource, &message));
		if (result)
		{
			mu::string message_l (message.begin (), message.end ());
			context_a.errors (message_l);
			valid = false;
		}
	}
	return valid;
}

mu::string mu::llvm_::linker::link_modules::name ()
{
	return mu::string (U"mu::llvm_::linker::link_modules");
}