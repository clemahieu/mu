#include "create.h"

#include <core/errors/error_target.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_llvm/apint/node.h>
#include <lambda_p_llvm/integer_type/node.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::integer_type::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::context::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_llvm::apint::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto bits (two->value->getLimitedValue ());
			if (bits >= llvm::IntegerType::MIN_INT_BITS && bits <= llvm::IntegerType::MAX_INT_BITS)
			{
				results.push_back (boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::IntegerType::get (*one->context, bits)));
			}
			else
			{
				std::wstringstream message;
				message << L"Bits is not within bounds: ";
				message << llvm::IntegerType::MIN_INT_BITS;
				message << L" <= ";
				message << two->value;
				message << L" <= ";
				message << llvm::IntegerType::MAX_INT_BITS;
				(*errors_a) (message.str ());
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

size_t lambda_p_llvm::integer_type::create::count ()
{
	return 2;
}

std::wstring lambda_p_llvm::integer_type::create::name ()
{
	return std::wstring (L"lambda_p_llvm::integer_type::create");
}