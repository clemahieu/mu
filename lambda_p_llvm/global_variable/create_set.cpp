#include "create_set.h"

#include <lambda_p_llvm/constant/node.h>
#include <lambda_p_llvm/global_variable/node.h>
#include <lambda_p_llvm/type/node.h>

#include <boost/make_shared.hpp>

#include <llvm/GlobalVariable.h>

void lambda_p_llvm::global_variable::create_set::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::constant::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		results.push_back (boost::make_shared <lambda_p_llvm::global_variable::node> (new llvm::GlobalVariable (one->type->type (), true, llvm::GlobalValue::LinkageTypes::PrivateLinkage, one->constant ()), one->type));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::global_variable::create_set::count ()
{
	return 1;
}