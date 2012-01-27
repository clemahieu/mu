#include "integer.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/apint/node.h>
#include <lambda_p_llvm/constant/node.h>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::constants::integer::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	if (parameters_a.size () == 2)
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_llvm::apint::node> (parameters_a [0]));
		auto two (boost::dynamic_pointer_cast <lambda_p_llvm::apint::node> (parameters_a [1]));
		if (one.get () != nullptr)
		{
			if (two.get () != nullptr)
			{
				auto bits (one->value->getLimitedValue ());
				if (bits <= llvm::IntegerType::MAX_INT_BITS && bits >= llvm::IntegerType::MIN_INT_BITS)
				{
					if (two->value->getActiveBits () <= bits)
					{
						auto value (llvm::ConstantInt::get (llvm::Type::getIntNTy (context_a->getContext (), bits), llvm::APInt (bits, two->value->getLimitedValue ())));
						results_a.push_back (boost::make_shared <lambda_p_llvm::constant::node> (value));
					}
					else
					{
						std::wstringstream message;
						message << name ();
						message << L": Value: ";
						message << two->value->getLimitedValue ();
						message << L" does not fit in the requested bit size: ";
						message << bits;
						(*errors_a) (message.str ());
					}
				}
				else
				{
					std::wstringstream message;
					message << name ();
					message << L": number of bits: ";
					message << bits;
					message << L" must be between: ";
					message << llvm::IntegerType::MIN_INT_BITS;
					message << L" and: ";
					message << llvm::IntegerType::MAX_INT_BITS;
					(*errors_a) (message.str ());
				}
			}
			else
			{
				invalid_type (errors_a, 1);
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
		message << name ();
		message << L" expecting two arguments, have: ";
		message << parameters_a.size ();
		(*errors_a) (message.str ());
	}
}