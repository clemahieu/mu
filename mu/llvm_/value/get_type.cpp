#include "get_type.h"

#include <mu/llvm_/value/node.h>
#include <mu/llvm_/type/build.h>
#include <mu/llvm_/type/node.h>
#include <mu/llvm_/context/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Value.h>

void mu::llvm_::value::get_type::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
	if (one.get () != nullptr)
	{
		mu::llvm_::type::build build (boost::make_shared <mu::llvm_::context::node> (&one->value ()->getContext ()), one->value ()->getType ());
		context_a.results.push_back (build.type);
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::value::get_type::count ()
{
	return 1;
}