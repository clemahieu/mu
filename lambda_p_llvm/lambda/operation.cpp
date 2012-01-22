#include "operation.h"

lambda_p_llvm::lambda::operation::operation (boost::shared_ptr <lambda_p::routine> routine_a)
	: routine (routine_a)
{
}

void lambda_p_llvm::lambda::operation::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a) 
{
	assert (false);
}