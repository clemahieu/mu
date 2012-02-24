#include "icmp.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/llvm_/predicate/node.h>
#include <mu/llvm_/integer_type/node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::instructions::icmp::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters_a, std::vector <boost::shared_ptr <mu::core::node>> & results_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::predicate::node> (parameters_a [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::value::node> (parameters_a [1]));
	auto three (boost::dynamic_pointer_cast <mu::llvm_::value::node> (parameters_a [2]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (three.get () != nullptr)
			{
				bool two_int (two->value ()->getType ()->isIntegerTy ());
				bool three_int (three->value ()->getType ()->isIntegerTy ());
				if (two_int && three_int)
				{
					size_t one_bits (two->value ()->getType ()->getPrimitiveSizeInBits ());
					size_t two_bits (three->value ()->getType ()->getPrimitiveSizeInBits ());
					if (one_bits == two_bits)
					{
						auto instruction (new llvm::ICmpInst (one->value, two->value (), three->value ()));
						results_a.push_back (boost::make_shared <mu::llvm_::instruction::node> (instruction, boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (two->value ()->getContext ()))));
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
					message << two_int;
					message << L" ";
					message << three_int;
					(*errors_a) (message.str ());
				}
			}
			else
			{
				invalid_type (errors_a, parameters_a [2], 2);
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

size_t mu::llvm_::instructions::icmp::count ()
{
	return 3;
}

std::wstring mu::llvm_::instructions::icmp::name ()
{
	return std::wstring (L"mu::llvm_::instructions::icmp");
}