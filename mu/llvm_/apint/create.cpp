#include "create.h"

#include <mu/script/integer/node.h>
#include <mu/llvm_/apint/node.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

#include <llvm/ADT/APInt.h>

void mu::llvm_::apint::create::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::integer::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::script::integer::node> (context_a.parameters [0]));
		context_a.results.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, one->value)));
	}
}

size_t mu::llvm_::apint::create::count ()
{
	return 1;
}