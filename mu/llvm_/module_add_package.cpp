#include <mu/llvm_/module_add_package.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/package_node.h>
#include <mu/llvm_/module_node.h>
#include <mu/llvm_/function_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Function.h>

#include <sstream>

bool mu::llvm_::module::add_package::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::llvm_::module::node, mu::script::package::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::module::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::package::node *> (context_a.parameters (1)));
		auto good (true);
		for (auto i (two->items.begin ()), j (two->items.end ()); i != j && good; ++i)
		{
			auto source (dynamic_cast <mu::llvm_::function::node *> (i->second));
			if (source != nullptr)
			{
				auto function (llvm::dyn_cast <llvm::Function> (source->value ()));
				if (function != nullptr)
				{
					llvm::Function::Create (function->getFunctionType (), llvm::GlobalValue::ExternalLinkage, function->getName (), one->module);
				}
			}
			else
			{
				auto source (dynamic_cast <mu::llvm_::function::node *> (i->second));
				if (source != nullptr)
				{
					auto function (llvm::dyn_cast <llvm::Function> (source->value ()));
					llvm::Function::Create (function->getFunctionType (), llvm::GlobalValue::ExternalLinkage, function->getName (), one->module);
				}
				else
				{
					mu::stringstream message;
					message << U"Operation: ";
					message << name ();
					message << U" package item: \"";
					message << i->first;
					message << U"\" is not an mu::llvm_::function::node: ";
					message << i->second->name ();
					context_a.errors (message.str ());
					result = false;
				}
			}
		}
	}
	return result;
}