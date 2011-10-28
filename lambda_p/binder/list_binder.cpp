#include "list_binder.h"

#include <lambda_p/binder/node_list.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/node_list.h>

void lambda_p::binder::list_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes_a, lambda_p::errors::error_list & problems)
{
	if (statement->association->results.size () == 1)
	{
		boost::shared_ptr <lambda_p::binder::list> set (new lambda_p::binder::list);
		for (auto i = statement->association->parameters.begin (); i != statement->association->parameters.end (); ++i)
		{
			set->nodes.push_back (nodes_a [*i]);
		}
		nodes_a [statement->association->results [0]] = set;
	}
	else
	{
		add_error (std::wstring (L"expecting 1 result"), problems);
	}
}

std::wstring lambda_p::binder::list_binder::binder_name ()
{
	return std::wstring (L"list_binder");
}