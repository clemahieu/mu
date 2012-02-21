#include "create.h"

#include <lambda_p_script/integer/node.h>
#include <lambda_p_llvm/apint/node.h>

#include <boost/make_shared.hpp>

#include <llvm/ADT/APInt.h>

void lambda_p_llvm::apint::create::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_script::integer::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		results.push_back (boost::make_shared <lambda_p_llvm::apint::node> (new llvm::APInt (64, one->value)));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::apint::create::count ()
{
	return 1;
}