#include "jit_function.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm/execution_engine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_llvm/fo_value.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

void lambda_p_llvm::jit_function::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (0, 2, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_llvm::execution_engine> engine (boost::dynamic_pointer_cast <lambda_p_llvm::execution_engine> (nodes [statement->association->references [0]]));
		check_binder (engine, 0, L"execution_engine", problems);
		boost::shared_ptr <lambda_p_llvm::fo_value> value (boost::dynamic_pointer_cast <lambda_p_llvm::fo_value> (nodes [statement->association->references [1]]));
		check_binder (value, 1, L"fo_value", problems);
		if (problems.errors.empty ())
		{
			llvm::Function * function (llvm::dyn_cast <llvm::Function> (value->value));
			if (function != nullptr)
			{
				engine->engine->runFunction (function, std::vector <llvm::GenericValue> ());
			}
			else
			{
				add_error (L"value is not a function", problems);
			}
		}
	}
}

std::wstring lambda_p_llvm::jit_function::binder_name ()
{
	return std::wstring (L"jit_function");
}