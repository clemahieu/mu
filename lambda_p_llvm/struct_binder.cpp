#include "struct_binder.h"

#include <lambda_p/binder/list.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p_llvm/generation_context.h>

#include <llvm/DerivedTypes.h>

lambda_p_llvm::struct_binder::struct_binder (lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::struct_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p::binder::list> list (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [statement->association->references [0]]));
		if (list.get () != nullptr)
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
					add_error (std::wstring (L"Expecting type"), problems);
				}
			}
			if (problems.errors.empty ())
			{
				llvm::StructType * type (llvm::StructType::get (context.context, types, false));
				boost::shared_ptr <lambda_p_llvm::type> new_type (new lambda_p_llvm::type (type));
				nodes [statement->association->declarations [0]] = new_type;
			}
		}
		else
		{
			unexpected_binder_type_error (0, std::wstring (L"struct_binder"), problems);
		}
	}
}

std::wstring lambda_p_llvm::struct_binder::binder_name ()
{
	return std::wstring (L"struct_binder");
}