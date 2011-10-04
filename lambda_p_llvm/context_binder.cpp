#include "context_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p_llvm/context.h>

#include <sstream>

lambda_p_llvm::context_binder::context_binder(void)
{
}

lambda_p_llvm::context_binder::~context_binder(void)
{
}

void lambda_p_llvm::context_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count == 2)
	{
		::lambda_p::core::node * node (statement->arguments [1]);
		::lambda_p::core::node_id node_type (node->node_type ());
		switch (node_type)
		{
			case ::lambda_p::core::node_declaration:
				{
					::boost::shared_ptr < ::lambda_p_llvm::context> context (new ::lambda_p_llvm::context);
					instances [node] = context;
				}
				break;
			default:
				problems << L"context_binder is expecting argument 1 to be a declaration, have: ";
				problems << node->node_type_name ();
				problems << '\n';
				break;
		}
	}
	else
	{
		problems << L"context_binder is expecting 1 argument, have: ";
		problems << argument_count;
		problems << '\n';
	}
}