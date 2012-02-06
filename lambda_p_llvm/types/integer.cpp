#include "integer.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/instruction/node.h>
#include <lambda_p_llvm/apint/node.h>
#include <lambda_p_llvm/integer_type/node.h>
#include <lambda_p_llvm/context/node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::types::integer::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::context::node> (parameters_a [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_llvm::apint::node> (parameters_a [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (two->value->getLimitedValue () <= llvm::IntegerType::MAX_INT_BITS && two->value->getLimitedValue () >= llvm::IntegerType::MIN_INT_BITS)
			{				
				results_a.push_back (boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::IntegerType::get (one->context, two->value->getLimitedValue ())));
			}
			else
			{
				std::wstringstream message;
				message << L"Invalid number of integer bits: ";
				message << two->value->getLimitedValue ();
				message << L" must be between: ";
				message << llvm::IntegerType::MIN_INT_BITS;
				message << L" and: ";
				message << llvm::IntegerType::MAX_INT_BITS;
				(*errors_a) (message.str ());
			}
		}
		else
		{
			invalid_type (errors_a, parameters_a [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters_a [0], 0);
	}
}

size_t lambda_p_llvm::types::integer::count ()
{
	return 2;
}