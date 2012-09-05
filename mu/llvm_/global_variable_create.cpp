#include <mu/llvm_/global_variable_create.h>

#include <mu/llvm_/type_node.h>
#include <mu/llvm_/global_variable_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/GlobalVariable.h>

#include <gc_cpp.h>

bool mu::llvm_::global_variable::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::llvm_::type::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::type::node *> (context_a.parameters (0)));
		context_a.push (new (GC) mu::llvm_::global_variable::node (new llvm::GlobalVariable (one->type (), false, llvm::GlobalValue::PrivateLinkage), one));
	}
	return valid;
}