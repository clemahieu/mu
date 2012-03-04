#include <mu/llvm_/apint.create.h>

#include <mu/script/integer.node.h>
#include <mu/llvm_/apint.node.h>

#include <boost/make_shared.hpp>

#include <llvm/ADT/APInt.h>

void mu::llvm_::apint::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::integer::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		results.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, one->value)));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::llvm_::apint::create::count ()
{
	return 1;
}
