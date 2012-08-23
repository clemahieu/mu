#include <mu/llvm_/apint/create.h>

#include <mu/script/integer/node.h>
#include <mu/llvm_/apint/node.h>
#include <mu/core/check.h>
#include <mu/llvm_/ctx.h>

#include <llvm/ADT/APInt.h>

#include <gc_cpp.h>

bool mu::llvm_::apint::create::operator () (mu::llvm_::ctx & context_a)
{
	bool valid (context_a.check <mu::script::integer::node> (context_a.errors));
	if (valid)
	{
		auto one (static_cast <mu::script::integer::node *> (context_a.working [0]));
        context_a.working.clear ();
		context_a.working.push_back (new (GC) mu::llvm_::apint::node (new llvm::APInt (64, one->value)));
	}
	return valid;
}