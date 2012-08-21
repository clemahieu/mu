#include <mu/llvm_/apint/create.h>

#include <mu/script/integer/node.h>
#include <mu/llvm_/apint/node.h>
#include <mu/core/check.h>
#include <mu/llvm_/ctx.h>

#include <llvm/ADT/APInt.h>

#include <gc_cpp.h>

bool mu::llvm_::apint::create::operator () (mu::llvm_::ctx & context_a)
{
	bool valid (mu::core::check <mu::script::integer::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::script::integer::node *> (context_a.parameters (0)));
		context_a.push (new (GC) mu::llvm_::apint::node (new llvm::APInt (64, one->value)));
	}
	return valid;
}