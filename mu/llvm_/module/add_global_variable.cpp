#include <mu/llvm_/module/add_global_variable.h>

#include <mu/llvm_/global_variable/node.h>
#include <mu/llvm_/module/node.h>
#include <mu/script/check.h>

#include <llvm/Module.h>

#include <gc_cpp.h>

bool mu::llvm_::module::add_global_variable::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::module::node, mu::llvm_::global_variable::node> () (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::module::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::llvm_::global_variable::node *> (context_a.parameters (1)));
		one->module->getGlobalList ().push_back (two->global_variable ());
	}
	return result;
}