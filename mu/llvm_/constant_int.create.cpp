#include <mu/llvm_/constant_int.create.h>

#include <mu/core/errors.error_target.h>
#include <mu/llvm_/context.node.h>
#include <mu/llvm_/apint.node.h>
#include <mu/llvm_/constant_int.node.h>
#include <mu/llvm_/integer_type.node.h>

#include <boost/make_shared.hpp>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>

#include <sstream>

void mu::llvm_::constant_int::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::context::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::apint::node> (parameters [1]));
	auto three (boost::dynamic_pointer_cast <mu::llvm_::apint::node> (parameters [2]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (three.get () != nullptr)
			{
				auto bits (two->value->getLimitedValue ());
				if (bits >= llvm::IntegerType::MIN_INT_BITS && bits <= llvm::IntegerType::MAX_INT_BITS)
				{
					if (three->value->getActiveBits () <= bits)
					{
						auto type (llvm::Type::getIntNTy (*one->context, bits));
						results.push_back (boost::make_shared <mu::llvm_::constant_int::node> (llvm::ConstantInt::get (*one->context, llvm::APInt (bits, three->value->getLimitedValue ())), boost::make_shared <mu::llvm_::integer_type::node> (type)));
					}
					else
					{
						std::wstringstream message;
						message << L"Number: ";
						message << three->value->getLimitedValue ();
						message << L" does not fit in: ";
						message << bits;
						message << L" bits";
						(*errors_a) (message.str ());
					}
				}
				else
				{
					std::wstringstream message;
					message << L"Number of bits: ";
					message << bits;
					message << L" is not between: ";
					message << llvm::IntegerType::MIN_INT_BITS;
					message << L" and: ";
					message << llvm::IntegerType::MAX_INT_BITS;
					(*errors_a) (message.str ());
				}
			}
			else
			{
				invalid_type (errors_a, parameters [2], 2);
			}
		}
		else
		{
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::llvm_::constant_int::create::count ()
{
	return 3;
}
