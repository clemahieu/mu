#include <mu/llvm_/global_variable/create.h>

#include <mu/llvm_/type/node.h>
#include <mu/llvm_/global_variable/node.h>
#include <mu/script/check.h>

#include <llvm/GlobalVariable.h>

#include <gc_cpp.h>

bool mu::llvm_::global_variable::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::llvm_::type::node> () (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::type::node *> (context_a.parameters (0)));
		context_a.push (new (GC) mu::llvm_::global_variable::node (new llvm::GlobalVariable (one->type (), false, llvm::GlobalValue::PrivateLinkage), one));
	}
	return valid;
}