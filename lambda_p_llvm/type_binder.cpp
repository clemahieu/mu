#define __STDC_LIMIT_MACROS

#include "type_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p/core/declaration.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/binder_string_error.h>
#include <lambda_p_llvm/generation_context.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

lambda_p_llvm::type_binder::type_binder (::lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::type_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.empty ())
	{
		::lambda_p::core::declaration * declaration (statement->association->results [0]);
		::lambda_p::core::node * command (statement->association->parameters [0]);
		::lambda_p::core::node_id command_type (command->node_type ());
		switch (command_type)
		{
		case ::lambda_p::core::node_data:
			{
				::lambda_p::binder::data * command_data (static_cast < ::lambda_p::binder::data *> (command));
				if (command_data->string ().compare (::std::wstring (L"getInt32Ty")) == 0)
				{
					::boost::shared_ptr < ::lambda_p_llvm::type> type (new ::lambda_p_llvm::type (::llvm::Type::getInt32Ty (context.context)));
					instances [declaration] = type;
				}
                else if (command_data->string ().compare (::std::wstring (L"getInt64PtrTy")) == 0)
                {
                    ::boost::shared_ptr < ::lambda_p_llvm::type> type (new ::lambda_p_llvm::type (::llvm::Type::getInt64PtrTy (context.context)));
                    instances [declaration] = type;
                }
				else if (command_data->string ().compare (::std::wstring (L"getInt1Ty")) == 0)
				{
					::boost::shared_ptr < ::lambda_p_llvm::type> type (new ::lambda_p_llvm::type (::llvm::Type::getInt1Ty (context.context)));
					instances [declaration] = type;
				}
				else
				{
					::std::wstring message;
					message.append (L"Unknown type_binder command: ");
					message.append (command_data->string ());
					add_error (message, problems);
				}
			}
			break;
		default:
			::std::wstring message;
			message.append (L"type_binder expects argument 1 to be data, have: ");
			message.append (::lambda_p::core::node_name (command_type));
			add_error (message, problems);
		}
	}
}

::std::wstring lambda_p_llvm::type_binder::binder_name ()
{
	return ::std::wstring (L"type_binder");
}