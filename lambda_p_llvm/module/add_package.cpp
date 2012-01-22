#include "add_package.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/package/node.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_llvm/function/node.h>

#include <llvm/Function.h>

#include <sstream>

void lambda_p_llvm::module::add_package::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::package::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto good (true);
			for (auto i (two->items.begin ()), j (two->items.end ()); i != j && good; ++i)
			{
				auto source (boost::dynamic_pointer_cast <lambda_p_llvm::function::node> (i->second));
				if (source.get () != nullptr)
				{
					llvm::Function::Create (source->function ()->getFunctionType (), llvm::GlobalValue::ExternalLinkage, source->function ()->getName (), one->module);
				}
				else
				{
					std::wstringstream message;
					message << L"Operation: ";
					message << name ();
					message << L" package item: \"";
					message << i->first;
					message << L"\" is not an lambda_p_llvm::function::node: ";
					message << i->second->name ();
					(*errors_a) (message.str ());
				}
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

size_t lambda_p_llvm::module::add_package::count ()
{
	return 2;
}

std::wstring lambda_p_llvm::module::add_package::name ()
{
	return std::wstring (L"lambda_p_llvm::module::add_package");
}