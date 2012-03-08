#include "create_int.h"

#include <mu/script/integer/node.h>
#include <mu/llvm_/execution_engine/generic_value/node.h>

#include <boost/make_shared.hpp>

void mu::llvm_::execution_engine::generic_value::create_int::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::script::integer::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::integer::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto result (boost::make_shared <mu::llvm_::execution_engine::generic_value::node> ());
			result->value.IntVal = llvm::APInt ((unsigned int) (one->value), (uint64_t) (two->value));
			context_a.results.push_back (result);
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [1], 1);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::execution_engine::generic_value::create_int::count ()
{
	return 2;
}