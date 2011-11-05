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
#include <lambda_p/binder/node.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/errors/error_list.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

lambda_p_llvm::type_binder::type_binder (lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::type_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		size_t declaration (statement->association->declarations [0]);
		size_t command (statement->association->references [0]);
		boost::shared_ptr <lambda_p::binder::node> command_instance (nodes [command]);
		boost::shared_ptr <lambda_p::binder::data> command_data (boost::dynamic_pointer_cast <lambda_p::binder::data> (command_instance));
		if (command_data.get () != nullptr)
		{
			if (command_data->string ().compare (std::wstring (L"getInt32Ty")) == 0)
			{
				boost::shared_ptr <lambda_p_llvm::type> type (new lambda_p_llvm::type (llvm::Type::getInt32Ty (context.context)));
				nodes [declaration] = type;
			}
            else if (command_data->string ().compare (std::wstring (L"getInt64PtrTy")) == 0)
            {
                boost::shared_ptr <lambda_p_llvm::type> type (new lambda_p_llvm::type (llvm::Type::getInt64PtrTy (context.context)));
                nodes [declaration] = type;
            }
			else if (command_data->string ().compare (std::wstring (L"getInt1Ty")) == 0)
			{
				boost::shared_ptr <lambda_p_llvm::type> type (new lambda_p_llvm::type (llvm::Type::getInt1Ty (context.context)));
				nodes [declaration] = type;
			}
			else if (command_data->string ().compare (std::wstring (L"getInt8PtrTy")) == 0)
			{
				boost::shared_ptr <lambda_p_llvm::type> type (new lambda_p_llvm::type (llvm::Type::getInt8PtrTy (context.context)));
				nodes [declaration] = type;
			}
			else if (command_data->string ().compare (std::wstring (L"getInt64Ty")) == 0)
			{
				boost::shared_ptr <lambda_p_llvm::type> type (new lambda_p_llvm::type (llvm::Type::getInt64Ty (context.context)));
				nodes [declaration] = type;
			}
			else
			{
				std::wstring message;
				message.append (L"Unknown type_binder command: ");
				message.append (command_data->string ());
				add_error (message, problems);
			}
		}
		else
		{
			problems (new lambda_p::errors::unexpected_binder_type (binder_name (), 1, std::wstring (L"data")));
		}
	}
}

std::wstring lambda_p_llvm::type_binder::binder_name ()
{
	return std::wstring (L"type_binder");
}