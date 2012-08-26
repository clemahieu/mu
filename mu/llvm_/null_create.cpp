#include <mu/llvm_/null_create.h>

#include <mu/llvm_/pointer_type_node.h>
#include <mu/llvm_/value_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Constants.h>

#include <gc_cpp.h>

bool mu::llvm_::null::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::llvm_::pointer_type::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::pointer_type::node *> (context_a.parameters (0)));
		context_a.push (new (GC) mu::llvm_::value::node (llvm::ConstantPointerNull::get (one->pointer_type ()), one));
	}
	return valid;
}