#include "llvm_context_new.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p_llvm/llvm_context.h>
#include <lambda_p/binder/command_list.h>

#include <sstream>

lambda_p_llvm::llvm_context_new::llvm_context_new(::boost::shared_ptr < ::lambda_p::binder::command_list> commands_a)
	: commands (commands_a)
{
}

lambda_p_llvm::llvm_context_new::~llvm_context_new(void)
{
}

void lambda_p_llvm::llvm_context_new::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
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
				::boost::shared_ptr < ::lambda_p_llvm::llvm_context> context (new ::lambda_p_llvm::llvm_context);
				commands->add_instance (context);
				instances [node] = context;
			}
			break;
		default:
			problems << L"llvm_context_new is expecting argument 1 to be a declaration, have: ";
			problems << node->node_type_name ();
			problems << '\n';
			break;
		}
	}
	else
	{
		problems << L"llvm_context_new is expecting 1 argument, have: ";
		problems << argument_count - 1;
		problems << '\n';
	}
}