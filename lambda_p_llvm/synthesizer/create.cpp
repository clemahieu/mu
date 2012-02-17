#include "create.h"

#include <boost/make_shared.hpp>

#include <lambda_p_llvm/synthesizer/operation.h>

void lambda_p_llvm::synthesizer::create::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	results.push_back (boost::make_shared <lambda_p_llvm::synthesizer::operation> ());
}

size_t lambda_p_llvm::synthesizer::create::count ()
{
	return 0;
}