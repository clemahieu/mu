#include "context_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/routine_instances.h>

#include <sstream>

lambda_p_llvm::context_binder::context_binder(void)
{
}

lambda_p_llvm::context_binder::~context_binder(void)
{
}

void lambda_p_llvm::context_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems)
{
	check_count (1, 0, statement, problems);
	if (problems.empty ())
	{
		boost::shared_ptr < lambda_p_llvm::context> context (new lambda_p_llvm::context);
		instances [statement->association->results [0]] = context;
	}
}

std::wstring lambda_p_llvm::context_binder::binder_name ()
{
	return std::wstring (L"context_binder");
}