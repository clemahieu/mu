#include "create.h"

#include <lambda_p_llvm_wrapper/context/node.h>

void lambda_p_llvm_wrapper::context::create::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	results.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm_wrapper::context::node));
}

size_t lambda_p_llvm_wrapper::context::create::count ()
{
	return 0;
}

std::wstring lambda_p_llvm_wrapper::context::create::name ()
{
	return std::wstring (L"lambda_p_llvm_wrapper::context::create");
}