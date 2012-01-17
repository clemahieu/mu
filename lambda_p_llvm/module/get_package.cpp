#include "get_package.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_script/package/node.h>
#include <lambda_p_llvm/function/node.h>

#include <llvm/Module.h>

#include <sstream>

void lambda_p_llvm::module::get_package::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		auto package (boost::shared_ptr <lambda_p_script::package::node> (new lambda_p_script::package::node));
		for (auto i (one->module->getFunctionList ().begin ()), j (one->module->getFunctionList ().end ()); i != j; ++i)
		{
			llvm::Function * function (i);
			auto name (i->getNameStr ());
			std::wstring wname (name.begin (), name.end ());
			package->items [wname] = boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::function::node (function));
			function->setName (llvm::Twine ());
		}
		one->module->getFunctionList ().clear ();
		results.push_back (package);
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::module::get_package::count ()
{
	return 1;
}

std::wstring lambda_p_llvm::module::get_package::name ()
{
	return std::wstring (L"lambda_p_llvm::module::get_package");
}