#include "context_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p/core/declaration.h>

#include <sstream>

lambda_p_llvm::context_binder::context_binder(void)
{
}

lambda_p_llvm::context_binder::~context_binder(void)
{
}

void lambda_p_llvm::context_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	bool problem (false);
	check_count (problem, 1, 0, L"context_binder", statement, problems);
	if (!problem)
	{
		::boost::shared_ptr < ::lambda_p_llvm::context> context (new ::lambda_p_llvm::context);
		instances [statement->results [0]] = context;
	}
}