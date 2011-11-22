#define __STDC_LIMIT_MACROS

#include "type_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_kernel/nodes/data.h>
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

void lambda_p_llvm::type_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		auto context (boost::dynamic_pointer_cast <lambda_p_llvm::context> (nodes [statement->association->references [0]]));
		check_binder (context, 0, L"context", problems);
		auto command (boost::dynamic_pointer_cast <lambda_p_kernel::nodes::data> (nodes [statement->association->references [1]]));
		check_binder (command, 1, L"data", problems);
		if (problems.errors.empty ())
		{
			if (command->string ().compare (std::wstring (L"getInt32Ty")) == 0)
			{
				boost::shared_ptr <lambda_p_llvm::type> type (new lambda_p_llvm::type (llvm::Type::getInt32Ty (context->context_m)));
				nodes [statement->association->declarations [0]] = type;
			}
            else if (command->string ().compare (std::wstring (L"getInt64PtrTy")) == 0)
            {
                boost::shared_ptr <lambda_p_llvm::type> type (new lambda_p_llvm::type (llvm::Type::getInt64PtrTy (context->context_m)));
                nodes [statement->association->declarations [0]] = type;
            }
			else if (command->string ().compare (std::wstring (L"getInt1Ty")) == 0)
			{
				boost::shared_ptr <lambda_p_llvm::type> type (new lambda_p_llvm::type (llvm::Type::getInt1Ty (context->context_m)));
				nodes [statement->association->declarations [0]] = type;
			}
			else if (command->string ().compare (std::wstring (L"getInt8PtrTy")) == 0)
			{
				boost::shared_ptr <lambda_p_llvm::type> type (new lambda_p_llvm::type (llvm::Type::getInt8PtrTy (context->context_m)));
				nodes [statement->association->declarations [0]] = type;
			}
			else if (command->string ().compare (std::wstring (L"getInt64Ty")) == 0)
			{
				boost::shared_ptr <lambda_p_llvm::type> type (new lambda_p_llvm::type (llvm::Type::getInt64Ty (context->context_m)));
				nodes [statement->association->declarations [0]] = type;
			}
			else
			{
				std::wstring message;
				message.append (L"Unknown type_binder command: ");
				message.append (command->string ());
				add_error (message, problems);
			}
		}
	}
}

std::wstring lambda_p_llvm::type_binder::binder_name ()
{
	return std::wstring (L"type_binder");
}