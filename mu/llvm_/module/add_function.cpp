#include "add_function.h"

#include <mu/llvm_/function/node.h>
#include <mu/llvm_/module/node.h>

#include <llvm/Module.h>

void mu::llvm_::module::add_function::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::module::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::function::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{			
			one->module->getFunctionList ().push_back (two->function ());
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

size_t mu::llvm_::module::add_function::count ()
{
	return 2;
}

std::wstring mu::llvm_::module::add_function::name ()
{
	return std::wstring (L"mu::llvm_::module::add_function");
}