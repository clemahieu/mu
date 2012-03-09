#include "get_package.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module/node.h>
#include <mu/script/package/node.h>
#include <mu/llvm_/function/node.h>
#include <mu/script/astring/node.h>
#include <mu/llvm_/type/build.h>
#include <mu/llvm_/context/node.h>
#include <mu/script/check.h>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::module::get_package::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::module::node, mu::script::astring::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::module::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::script::astring::node> (context_a.parameters [1]));
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
		context_a.results.push_back (package);
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