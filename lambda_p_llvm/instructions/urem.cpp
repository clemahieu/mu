#include "urem.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/value/node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::instructions::urem::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	if (check_size (errors_a, 2, parameters_a.size ()))
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters_a [0]));
		auto two (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters_a [1]));
		if (one.get () != nullptr)
		{
			if (two.get () != nullptr)
			{
				bool one_int (one->value ()->getType ()->isIntegerTy ());
				bool two_int (two->value ()->getType ()->isIntegerTy ());
				if (one_int && two_int)
				{
					size_t one_bits (one->value ()->getType ()->getPrimitiveSizeInBits ());
					size_t two_bits (two->value ()->getType ()->getPrimitiveSizeInBits ());
					if (one_bits == two_bits)
					{
						auto instruction (llvm::BinaryOperator::CreateURem (one->value (), two->value ()));
						context_a->getInstList ().push_back (instruction);
						results_a.push_back (boost::make_shared <lambda_p_llvm::value::node> (instruction));
					}
					else
					{
						std::wstringstream message;
						message << L"Bit widths don't match: ";
						message << one_bits;
						message << L" ";
						message << two_bits;
						(*errors_a) (message.str ());
					}
				}
				else
				{
					std::wstringstream message;
					message << L"Arguments are not integers: ";
					message << one_int;
					message << L" ";
					message << two_int;
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
}