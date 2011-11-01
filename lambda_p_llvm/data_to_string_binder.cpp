#define __STDC_LIMIT_MACROS

#include "data_to_string_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p_llvm/constant_wstring.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unexpected_binder_type.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p/errors/error_list.h>

#include <llvm/DerivedTypes.h>
#include <llvm/Constants.h>
#include <llvm/GlobalValue.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Module.h>

#include <sstream>

lambda_p_llvm::data_to_string_binder::data_to_string_binder (lambda_p_llvm::generation_context context_a)
: context (context_a)
{
}

lambda_p_llvm::data_to_string_binder::~data_to_string_binder (void)
{
}

void lambda_p_llvm::data_to_string_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p::binder::data> data (boost::dynamic_pointer_cast <lambda_p::binder::data> (nodes [statement->association->references [0]]));
		if (data.get () != nullptr)
		{
			lambda_p_llvm::constant_wstring string (context, data->string ());                        
			boost::shared_ptr <lambda_p_llvm::fo_value> value (new lambda_p_llvm::fo_value (string.value));
			nodes [statement->association->declarations [0]] = value;
		}
		else
		{
			problems (new lambda_p::errors::unexpected_binder_type (binder_name (), 0, std::wstring (L"data")));
		}
	}
}

std::wstring lambda_p_llvm::data_to_string_binder::binder_name ()
{
	return std::wstring (L"data_to_string_binder");
}