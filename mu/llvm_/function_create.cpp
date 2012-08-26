#include <mu/llvm_/function_create.h>

#include <mu/llvm_/function_type_node.h>
#include <mu/llvm_/function_node.h>
#include <mu/llvm_/pointer_type_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Function.h>

#include <gc_cpp.h>

bool mu::llvm_::function::create::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::llvm_::function_type::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::function_type::node *> (context_a.parameters (0)));
		context_a.push (new (GC) mu::llvm_::function::node (llvm::Function::Create (one->function_type (), llvm::GlobalValue::PrivateLinkage), new (GC) mu::llvm_::pointer_type::node (one)));
	}
	return result;
}