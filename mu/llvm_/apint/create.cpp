#include <mu/llvm_/apint/create.h>

#include <mu/script/integer/node.h>
#include <mu/llvm_/apint/node.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

#include <llvm/ADT/APInt.h>

bool mu::llvm_::apint::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::script::integer::node> () (context_a));
	if (valid)
	{
		auto one (boost::static_pointer_cast <mu::script::integer::node> (context_a.parameters (0)));
		context_a.push (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, one->value)));
	}
	return valid;
}