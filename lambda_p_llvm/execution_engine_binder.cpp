#include "execution_engine_binder.h"

#include <lambda_p_llvm/module.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/node_list.h>

void lambda_p_llvm::execution_engine_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_llvm::module> module (boost::dynamic_pointer_cast <lambda_p_llvm::module> (nodes [statement->association->references [0]]));
		if (module.get () != nullptr)
		{

		}
		else
		{
			unexpected_binder_type_error (0, L"module", problems);
		}
	}
}

std::wstring lambda_p_llvm::execution_engine_binder::binder_name ()
{
	return std::wstring (L"execution_engine_binder");
}