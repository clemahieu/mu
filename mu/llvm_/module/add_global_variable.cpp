#include "add_global_variable.h"

#include <mu/llvm_/global_variable/node.h>
#include <mu/llvm_/module/node.h>
#include <mu/script/check.h>

#include <llvm/Module.h>

void mu::llvm_::module::add_global_variable::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::module::node, mu::llvm_::global_variable::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::module::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::llvm_::global_variable::node> (context_a.parameters [1]));
		one->module->getGlobalList ().push_back (two->global_variable ());
	}
}