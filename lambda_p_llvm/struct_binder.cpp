#include "struct_binder.h"

#include <lambda_p/binder/list.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm/context.h>

#include <llvm/DerivedTypes.h>


void lambda_p_llvm::struct_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		auto context (boost::dynamic_pointer_cast <lambda_p_llvm::context> (nodes [statement->association->references [0]]));
		check_binder (context, 0, L"context", problems);
		auto list (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [statement->association->references [1]]));
		check_binder (list, 1, L"list", problems);
		if (problems.errors.empty ())
		{
			std::vector <llvm::Type const *> types;
			for (auto i = list->nodes.begin (); i != list->nodes.end (); ++i)
			{
				boost::shared_ptr <lambda_p_llvm::type> type (boost::dynamic_pointer_cast <lambda_p_llvm::type> (*i));
				if (type.get () != nullptr)
				{
					types.push_back (type->type_m);
				}
				else
				{
					add_error (L"Expecting type", problems);
				}
			}
			if (problems.errors.empty ())
			{
				llvm::StructType * type (llvm::StructType::get (context->context_m, types, false));
				nodes [statement->association->declarations [0]] = boost::shared_ptr <lambda_p_llvm::type> (new lambda_p_llvm::type (type));
			}
		}
	}
}

std::wstring lambda_p_llvm::struct_binder::binder_name ()
{
	return std::wstring (L"struct_binder");
}