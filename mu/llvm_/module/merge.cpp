#include "merge.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module/node.h>

#include <llvm/Linker.h>

#include <sstream>

void mu::llvm_::module::merge::perform (mu::script::context & context_a)
{
	if (context_a.parameters.size () > 0)
	{
		auto one (boost::dynamic_pointer_cast <mu::llvm_::module::node> (context_a.parameters [0]));
		if (one.get () != nullptr)
		{
			size_t position (1);
			for (auto i (context_a.parameters.begin () + 1), j (context_a.parameters.end () + 0); i != j; ++i, ++position)
			{
				auto module (boost::dynamic_pointer_cast <mu::llvm_::module::node> (*i));
				if (module.get () != nullptr)
				{
					std::string errors;
					llvm::Linker::LinkModules (one->module, module->module, llvm::Linker::DestroySource, &errors);
					if (!errors.empty ())
					{
						std::wstring errors_l (errors.begin (), errors.end ());
						(*context_a.errors) (errors_l);
					}
				}
				else
				{
					invalid_type (context_a.errors, context_a.parameters [position], position);
				}
			}
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [0], 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Operation: ";
		message << name ();
		message << L" requires at least 1 argument";
		(*context_a.errors) (message.str ());
	}
}