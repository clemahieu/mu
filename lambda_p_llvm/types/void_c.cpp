#include "void_c.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/void_type/node.h>

#include <llvm/Type.h>
#include <llvm/BasicBlock.h>

#include <boost/make_shared.hpp>

#include <sstream>

void lambda_p_llvm::types::void_c::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	if (parameters_a.size () == 0)
	{	
		results_a.push_back (boost::make_shared <lambda_p_llvm::void_type::node> (llvm::Type::getVoidTy (context_a->getContext ())));
	}
	else
	{
		std::wstringstream message;
		message << L"Void operation requires no arguments, have: ";
		message << parameters_a.size ();
		(*errors_a) (message.str ());
	}
}