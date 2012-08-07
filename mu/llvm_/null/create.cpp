#include <mu/llvm_/null/create.h>

#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/value/node.h>
#include <mu/script/check.h>

#include <llvm/Constants.h>

#include <gc_cpp.h>

bool mu::llvm_::null::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::llvm_::pointer_type::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::pointer_type::node *> (context_a.parameters (0)));
		context_a.push (new (GC) mu::llvm_::value::node (llvm::ConstantPointerNull::get (one->pointer_type ()), one));
	}
	return valid;
}