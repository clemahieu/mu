#include "add_package.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/package/node.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/function/node.h>

#include <llvm/Function.h>

#include <sstream>

void mu::llvm_::module::add_package::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::module::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::package::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto good (true);
			for (auto i (two->items.begin ()), j (two->items.end ()); i != j && good; ++i)
			{
				auto source (boost::dynamic_pointer_cast <mu::llvm_::function::node> (i->second));
				if (source.get () != nullptr)
				{
					auto function (llvm::dyn_cast <llvm::Function> (source->value ()));
					if (function != nullptr)
					{
						llvm::Function::Create (function->getFunctionType (), llvm::GlobalValue::ExternalLinkage, function->getName (), one->module);
					}
				}
				else
				{
					auto source (boost::dynamic_pointer_cast <mu::llvm_::function::node> (i->second));
					if (source.get () != nullptr)
					{
						auto function (llvm::dyn_cast <llvm::Function> (source->value ()));
						llvm::Function::Create (function->getFunctionType (), llvm::GlobalValue::ExternalLinkage, function->getName (), one->module);
					}
					else
					{
						std::wstringstream message;
						message << L"Operation: ";
						message << name ();
						message << L" package item: \"";
						message << i->first;
						message << L"\" is not an mu::llvm_::function::node: ";
						message << i->second->name ();
						(*context_a.errors) (message.str ());
					}
				}
			}
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [1], 1);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::module::add_package::count ()
{
	return 2;
}

std::wstring mu::llvm_::module::add_package::name ()
{
	return std::wstring (L"mu::llvm_::module::add_package");
}