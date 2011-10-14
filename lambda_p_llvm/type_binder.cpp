#define __STDC_LIMIT_MACROS

#include "type_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/binder_string_error.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/errors/unexpected_binder_type.h>
#include <lambda_p/binder/instance.h>
#include <lambda_p/binder/routine_instances.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

lambda_p_llvm::type_binder::type_binder (::lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::type_binder::bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.empty ())
	{
		size_t declaration (statement->association->results [0]);
		size_t command (statement->association->parameters [0]);
		::boost::shared_ptr < ::lambda_p::binder::instance> command_instance (instances [command]);
		::boost::shared_ptr < ::lambda_p::binder::data> command_data (::boost::dynamic_pointer_cast < ::lambda_p::binder::data> (command_instance));
		if (command_data.get () != NULL)
		{
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
		else
		{
			::boost::shared_ptr < ::lambda_p::errors::unexpected_binder_type> error (new ::lambda_p::errors::unexpected_binder_type (binder_name (), 1, ::std::wstring (L"data")));
			problems.push_back (error);
		}
	}
}

::std::wstring lambda_p_llvm::type_binder::binder_name ()
{
	return ::std::wstring (L"type_binder");
}