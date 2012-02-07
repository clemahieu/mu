#include "pointer.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/instruction/node.h>
#include <lambda_p_llvm/apint/node.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/context/node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::types::pointer::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	if (parameters_a.size () == 1)
	{	
		auto one (boost::dynamic_pointer_cast <lambda_p_llvm::type::node> (parameters_a [0]));
		if (one.get () != nullptr)
		{
			results_a.push_back (boost::make_shared <lambda_p_llvm::pointer_type::node> (one));
		}
		else
		{
			invalid_type (errors_a, parameters_a [0], 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Pointer operation requires one arguments, have: ";
		message << parameters_a.size ();
		(*errors_a) (message.str ());
	}
}

size_t lambda_p_llvm::types::pointer::count ()
{
	return 2;
}