#include "create.h"

#include <mu/script/integer/node.h>
#include <mu/llvm_/apint/node.h>

#include <boost/make_shared.hpp>

#include <llvm/ADT/APInt.h>

void mu::llvm_::apint::create::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::script::integer::node> (context_a.parameters [0]));
	if (one.get () != nullptr)
	{
		context_a.results.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, one->value)));
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::apint::create::count ()
{
	return 1;
}