#include <mu/llvm_/module/get_package.h>

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

#include <gc_cpp.h>

bool mu::llvm_::module::get_package::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::module::node, mu::script::astring::node> () (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::module::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::astring::node *> (context_a.parameters (1)));
		auto package (new (GC) mu::script::package::node);
		for (auto i (one->module->getFunctionList ().begin ()), j (one->module->getFunctionList ().end ()); i != j; ++i)
		{
			llvm::Function * function (i);
			auto name (i->getName ().str ());
			mu::string wname (name.begin (), name.end ());
			mu::llvm_::type::build build (new (GC) mu::llvm_::context::node (&function->getContext ()), function->getType ()); 
			package->items [wname] = new (GC) mu::llvm_::function::node (function, build.type);
			name.append (two->string);
			function->setName (name);
		}
		context_a.push (package);
	}
	return result;
}

mu::string mu::llvm_::module::get_package::name ()
{
	return mu::string (U"mu::llvm_::module::get_package");
}