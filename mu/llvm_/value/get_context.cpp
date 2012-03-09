#include "get_context.h"

#include <mu/llvm_/value/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/script/check.h>

#include <llvm/Value.h>

#include <boost/make_shared.hpp>

void mu::llvm_::value::get_context::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::value::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
		context_a.results.push_back (boost::make_shared <mu::llvm_::context::node> (&one->value ()->getContext ()));
	}
}

size_t mu::llvm_::value::get_context::count ()
{
	return 1;
}