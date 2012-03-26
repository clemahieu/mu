#include <mu/llvm_/module/get_function.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module/node.h>
#include <mu/script/astring/node.h>
#include <mu/llvm_/function/node.h>
#include <mu/llvm_/type/build.h>
#include <mu/llvm_/context/node.h>
#include <mu/script/check.h>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>

#include <sstream>

#include <boost/make_shared.hpp>

bool mu::llvm_::module::get_function::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::module::node, mu::script::astring::node> () (context_a));
	if (result)
	{
		auto one (boost::static_pointer_cast <mu::llvm_::module::node> (context_a.parameters (0)));
		auto two (boost::static_pointer_cast <mu::script::astring::node> (context_a.parameters (1)));
		auto function (one->module->getFunction (llvm::StringRef (two->string)));
		if (function != nullptr)
		{
			mu::llvm_::type::build build (boost::make_shared <mu::llvm_::context::node> (&function->getContext ()), function->getType ());
			context_a.push (boost::shared_ptr <mu::core::node> (new mu::llvm_::function::node (function, build.type)));
		}
		else
		{
			std::wstringstream message;
			message << L"Module has no function named: ";
			std::wstring name (two->string.begin (), two->string.end ());
			message << name;
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}

std::wstring mu::llvm_::module::get_function::name ()
{
	return std::wstring (L"mu::llvm_::module::get_function");
}