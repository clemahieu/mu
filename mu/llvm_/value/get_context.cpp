#include "get_context.h"

#include <mu/llvm_/value/node.h>
#include <mu/llvm_/context/node.h>

#include <llvm/Value.h>

#include <boost/make_shared.hpp>

void mu::llvm_::value::get_context::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
	if (one.get () != nullptr)
	{
		context_a.results.push_back (boost::make_shared <mu::llvm_::context::node> (&one->value ()->getContext ()));
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::value::get_context::count ()
{
	return 1;
}