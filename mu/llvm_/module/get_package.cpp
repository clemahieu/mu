#include "get_package.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module/node.h>
#include <mu/script/package/node.h>
#include <mu/llvm_/function/node.h>
#include <mu/script/astring/node.h>
#include <mu/llvm_/type/build.h>
#include <mu/llvm_/context/node.h>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::module::get_package::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::module::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::astring::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto package (boost::shared_ptr <mu::script::package::node> (new mu::script::package::node));
			for (auto i (one->module->getFunctionList ().begin ()), j (one->module->getFunctionList ().end ()); i != j; ++i)
			{
				llvm::Function * function (i);
				auto name (i->getNameStr ());
				std::wstring wname (name.begin (), name.end ());
				mu::llvm_::type::build build (boost::make_shared <mu::llvm_::context::node> (&function->getContext ()), function->getType ()); 
				package->items [wname] = boost::shared_ptr <mu::core::node> (new mu::llvm_::function::node (function, build.type));
				name.append (two->string);
				function->setName (name);
			}
			results.push_back (package);
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

size_t mu::llvm_::module::get_package::count ()
{
	return 2;
}

std::wstring mu::llvm_::module::get_package::name ()
{
	return std::wstring (L"mu::llvm_::module::get_package");
}