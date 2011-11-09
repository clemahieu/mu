#define __STDC_LIMIT_MACROS

#include "constant_int_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unexpected_binder_type.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_kernel/number.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/context.h>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>

#include <wchar.h>
#include <errno.h>

#include <sstream>

void lambda_p_llvm::constant_int_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)	
{
	check_count (1, 3, statement, problems);
	if (problems.errors.empty ())
	{
		auto context (boost::dynamic_pointer_cast <lambda_p_llvm::context> (nodes [statement->association->references [0]]));
		check_binder (context, 0, L"context", problems);
		auto number (boost::dynamic_pointer_cast <lambda_p_kernel::number> (nodes [statement->association->references [1]]));
		check_binder (number, 1, L"number", problems);
		auto bits (boost::dynamic_pointer_cast <lambda_p_kernel::number> (nodes [statement->association->references [2]]));
		check_binder (bits, 2, L"number", problems);
		if (problems.errors.empty ())
		{
			nodes [statement->association->declarations [0]] = boost::shared_ptr <lambda_p_llvm::value> (new lambda_p_llvm::value (llvm::ConstantInt::get (llvm::IntegerType::get (context->context_m, (unsigned int)bits->value), number->value)));
		}
	}
}

std::wstring lambda_p_llvm::constant_int_binder::binder_name ()
{
	return std::wstring (L"constant_int_binder");
}