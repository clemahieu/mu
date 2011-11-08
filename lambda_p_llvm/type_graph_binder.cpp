#include "type_graph_binder.h"

#include <lambda_p/binder/binder_implementor.h>
#include <lambda_p/core/routine.h>

void lambda_p_llvm::type_graph_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 2, statement, problems);
	if (problems.errors.empty ())
	{
		auto routine (boost::dynamic_pointer_cast <lambda_p::core::routine> (nodes [statement->association->references [0]]));
		check_binder (routine, 0, L"routine", problems);
		auto parameters (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [statement->association->references [1]]));
		check_binder (parameters, 1, L"list", problems);
		
	}
}

void lambda_p_llvm::type_graph_binder::core (boost::shared_ptr <lambda_p::core::routine> routine, boost::shared_ptr <lambda_p::binder::list> parameters, lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	for (auto i (0); i < routine->statements.size (); ++i)
	{

	}
}

std::wstring lambda_p_llvm::type_graph_binder::binder_name ()
{
	std::wstring (L"type_graph_binder");
}