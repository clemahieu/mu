#include <mu/llvm_/module/merge.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module/node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Linker.h>

#include <sstream>

bool mu::llvm_::module::merge::operator () (mu::script::context & context_a)
{
	bool valid (true);
	if (context_a.parameters_size () > 0)
	{
		auto one (dynamic_cast <mu::llvm_::module::node *> (context_a.parameters (0)));
		if (one != nullptr)
		{
			size_t position (1);
			for (auto i (context_a.parameters_begin () + 1), j (context_a.parameters_end () + 0); i != j; ++i, ++position)
			{
				auto module (dynamic_cast <mu::llvm_::module::node *> (*i));
				if (module != nullptr)
				{
					std::string errors;
					llvm::Linker::LinkModules (one->module, module->module, llvm::Linker::DestroySource, &errors);
					if (!errors.empty ())
					{
						mu::string errors_l (errors.begin (), errors.end ());
						context_a.errors (errors_l);
						valid = false;
					}
				}
				else
				{
					mu::core::type_fail (context_a.errors, typeid (mu::llvm_::module::node), context_a.parameters (position), position);
				}
			}
		}
		else
		{
			mu::core::type_fail (context_a.errors, typeid (mu::llvm_::module::node), context_a.parameters (0), 0);
		}
	}
	else
	{
		mu::stringstream message;
		message << L"Operation: ";
		message << name ();
		message << L" requires at least 1 argument";
		context_a.errors (message.str ());
		valid = false;
	}
	return valid;
}