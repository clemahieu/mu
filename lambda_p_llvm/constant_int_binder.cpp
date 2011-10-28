#define __STDC_LIMIT_MACROS

#include "constant_int_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unexpected_binder_type.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p_kernel/number.h>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>

#include <wchar.h>
#include <errno.h>

#include <sstream>

lambda_p_llvm::constant_int_binder::constant_int_binder (lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

lambda_p_llvm::constant_int_binder::~constant_int_binder(void)
{
}

void lambda_p_llvm::constant_int_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & instances, lambda_p::errors::error_list & problems)	
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_kernel::number> number (boost::dynamic_pointer_cast <lambda_p_kernel::number> (instances [statement->association->parameters [0]]));
		if (number.get () != nullptr)
		{
			boost::shared_ptr <lambda_p_kernel::number> bits (boost::dynamic_pointer_cast <lambda_p_kernel::number> (instances [statement->association->parameters [1]]));
			if (bits.get () != nullptr)
			{
				boost::shared_ptr <lambda_p_llvm::value> value (new lambda_p_llvm::fo_value (llvm::ConstantInt::get (llvm::IntegerType::get (context.context, (unsigned int)bits->value), number->value)));
				instances [statement->association->results [0]] = value;
			}
			else
			{
				unexpected_binder_type_error (1, std::wstring (L"number"), problems);
			}
		}
		else
		{
			unexpected_binder_type_error (0, std::wstring (L"number"), problems);
		}
	}
}

std::wstring lambda_p_llvm::constant_int_binder::binder_name ()
{
	return std::wstring (L"constant_int_binder");
}