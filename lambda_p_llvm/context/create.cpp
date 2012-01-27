#include "create.h"

#include <lambda_p_llvm/context/value.h>

void lambda_p_llvm::context::create::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	results.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::context::value));
}

size_t lambda_p_llvm::context::create::count ()
{
	return 0;
}

std::wstring lambda_p_llvm::context::create::name ()
{
	return std::wstring (L"lambda_p_llvm::context::create");
}