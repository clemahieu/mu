#include "add_function.h"

#include <mu/llvm_/function/node.h>
#include <mu/llvm_/module/node.h>
#include <mu/script/check.h>

#include <llvm/Module.h>

void mu::llvm_::module::add_function::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::module::node, mu::llvm_::function::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::module::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::llvm_::function::node> (context_a.parameters [1]));
		one->module->getFunctionList ().push_back (two->function ());
	}
}

std::wstring mu::llvm_::module::add_function::name ()
{
	return std::wstring (L"mu::llvm_::module::add_function");
}