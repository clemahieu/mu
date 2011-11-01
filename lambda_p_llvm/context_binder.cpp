#include "context_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p/errors/error_list.h>

#include <sstream>

lambda_p_llvm::context_binder::context_binder(void)
{
}

lambda_p_llvm::context_binder::~context_binder(void)
{
}

void lambda_p_llvm::context_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 0, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p_llvm::context> context (new lambda_p_llvm::context);
		nodes [statement->association->declarations [0]] = context;
	}
}

std::wstring lambda_p_llvm::context_binder::binder_name ()
{
	return std::wstring (L"context_binder");
}