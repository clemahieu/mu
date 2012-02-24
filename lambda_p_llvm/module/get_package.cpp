#include "get_package.h"

#include <core/errors/error_target.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_script/package/node.h>
#include <lambda_p_llvm/function/node.h>
#include <lambda_p_script/astring/node.h>
#include <lambda_p_llvm/type/build.h>
#include <lambda_p_llvm/context/node.h>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::module::get_package::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::astring::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto package (boost::shared_ptr <lambda_p_script::package::node> (new lambda_p_script::package::node));
			for (auto i (one->module->getFunctionList ().begin ()), j (one->module->getFunctionList ().end ()); i != j; ++i)
			{
				llvm::Function * function (i);
				auto name (i->getNameStr ());
				std::wstring wname (name.begin (), name.end ());
				lambda_p_llvm::type::build build (boost::make_shared <lambda_p_llvm::context::node> (&function->getContext ()), function->getType ()); 
				package->items [wname] = boost::shared_ptr <mu::core::node> (new lambda_p_llvm::function::node (function, build.type));
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

size_t lambda_p_llvm::module::get_package::count ()
{
	return 2;
}

std::wstring lambda_p_llvm::module::get_package::name ()
{
	return std::wstring (L"lambda_p_llvm::module::get_package");
}