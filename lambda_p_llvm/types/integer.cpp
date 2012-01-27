#include "integer.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/apint/node.h>
#include <lambda_p_llvm/integer_type/node.h>

#include <sstream>

#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>

#include <boost/make_shared.hpp>

void lambda_p_llvm::types::integer::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	if (parameters_a.size () == 1)
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_llvm::apint::node> (parameters_a [0]));
		if (one.get () != nullptr)
		{
			if (one->value->getLimitedValue () <= llvm::IntegerType::MAX_INT_BITS && one->value->getLimitedValue () >= llvm::IntegerType::MIN_INT_BITS)
			{				
				results_a.push_back (boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::IntegerType::get (context_a->getContext (), one->value->getLimitedValue ())));
			}
			else
			{
				std::wstringstream message;
				message << L"Invalid number of integer bits: ";
				message << one->value->getLimitedValue ();
				message << L" must be between: ";
				message << llvm::IntegerType::MIN_INT_BITS;
				message << L" and: ";
				message << llvm::IntegerType::MAX_INT_BITS;
				(*errors_a) (message.str ());
			}
		}
		else
		{
			invalid_type (errors_a, 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Integer operation requires one argument, have: ";
		message << parameters_a.size ();
		(*errors_a) (message.str ());
	}
}