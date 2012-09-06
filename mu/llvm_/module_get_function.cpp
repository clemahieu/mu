#include <mu/llvm_/module_get_function.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module_node.h>
#include <mu/script/astring_node.h>
#include <mu/llvm_/function_node.h>
#include <mu/llvm_/type_build.h>
#include <mu/llvm_/context_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::module::get_function::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::llvm_::module::node, mu::script::astring::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::module::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::astring::node *> (context_a.parameters (1)));
		auto function (one->module->getFunction (llvm::StringRef (two->string)));
		if (function != nullptr)
		{
			mu::llvm_::type::build build (new (GC) mu::llvm_::context::node (&function->getContext ()), function->getType ());
			context_a.push (new (GC) mu::llvm_::function::node (function, build.type));
		}
		else
		{
			mu::stringstream message;
			message << U"Module has no function named: ";
			mu::string name (two->string.begin (), two->string.end ());
			message << name;
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}

mu::string mu::llvm_::module::get_function::name ()
{
	return mu::string (U"mu::llvm_::module::get_function");
}