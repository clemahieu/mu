#include "create_int.h"

#include <mu/script/integer/node.h>
#include <mu/llvm_/execution_engine/generic_value/node.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

void mu::llvm_::execution_engine::generic_value::create_int::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::integer::node, mu::script::integer::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::script::integer::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::script::integer::node> (context_a.parameters [1]));
		auto result (boost::make_shared <mu::llvm_::execution_engine::generic_value::node> ());
		result->value.IntVal = llvm::APInt ((unsigned int) (one->value), (uint64_t) (two->value));
		context_a.results.push_back (result);
	}
}