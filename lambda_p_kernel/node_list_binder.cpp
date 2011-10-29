#include "node_list_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unexpected_result_count.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p/binder/list.h>

void lambda_p_kernel::node_list_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p::binder::list> list (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [statement->association->references [0]]));
		if (list.get () != nullptr)
		{
			boost::shared_ptr <lambda_p::binder::node_list> nodes_l (new lambda_p::binder::node_list);
			for (auto i = list->nodes.begin (); i != list->nodes.end (); ++i)
			{
				nodes_l->nodes.push_back (*i);
				nodes [statement->association->declarations [0]] = nodes_l;
			}
		}
		else
		{
			unexpected_binder_type_error (0, std::wstring (L"list"), problems);
		}
	}
}

std::wstring lambda_p_kernel::node_list_binder::binder_name ()
{
	return std::wstring (L"routine_nodes_binder");
}