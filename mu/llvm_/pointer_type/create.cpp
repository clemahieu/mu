#include <mu/llvm_/pointer_type/create.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/apint/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::pointer_type::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::llvm_::type::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::type::node *> (context_a.parameters (0)));
		context_a.push (new (GC) mu::llvm_::pointer_type::node (one));
	}
	return valid;
}