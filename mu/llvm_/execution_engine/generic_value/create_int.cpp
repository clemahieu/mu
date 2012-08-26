#include <mu/llvm_/execution_engine/generic_value/create_int.h>

#include <mu/script/integer_node.h>
#include <mu/llvm_/execution_engine/generic_value/node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <gc_cpp.h>

bool mu::llvm_::execution_engine::generic_value::create_int::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::script::integer::node, mu::script::integer::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::script::integer::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::integer::node *> (context_a.parameters (1)));
		auto result (new (GC) mu::llvm_::execution_engine::generic_value::node);
		result->value.IntVal = llvm::APInt ((unsigned int) (one->value), (uint64_t) (two->value));
		context_a.push (result);
	}
	return result;
}