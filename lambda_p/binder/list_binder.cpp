#include "list_binder.h"

#include <lambda_p/binder/list.h>
#include <lambda_p/core/expression.h>

void lambda_p::binder::list_binder::bind (lambda_p::core::expression * expression, std::map <lambda_p::core::expression *, boost::shared_ptr <lambda_p::binder::node>> & nodes_a, lambda_p::errors::error_list & problems)
{
	boost::shared_ptr <lambda_p::binder::list> set (new lambda_p::binder::list);
	for (auto i = expression->begin (), end (expression->end ()); i != end; ++i)
	{
		set->nodes.push_back (nodes_a [*i]);
	}
	nodes_a [expression] = set;
}

std::wstring lambda_p::binder::list_binder::binder_name ()
{
	return std::wstring (L"list_binder");
}