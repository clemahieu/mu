#include "routine_instances_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unexpected_result_count.h>
#include <lambda_p/binder/routine_instances.h>

lambda_p::binder::routine_instances_binder::routine_instances_binder(void)
{
}

void lambda_p::binder::routine_instances_binder::bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	if (statement->association->results.size () == 1)
	{
		::boost::shared_ptr < ::lambda_p::binder::routine_instances> instances_l (new ::lambda_p::binder::routine_instances);
		for (::std::vector < size_t>::iterator i = statement->association->parameters.begin (); i != statement->association->parameters.end (); ++i)
		{
			instances_l->instances.push_back (instances [*i]);
			instances [statement->association->results [0]] = instances_l;
		}
	}
	else
	{
		::boost::shared_ptr < ::lambda_p::errors::unexpected_result_count> error (new ::lambda_p::errors::unexpected_result_count (binder_name (), statement->association->results.size (), 1));
		problems.push_back (error);
	}
}

::std::wstring lambda_p::binder::routine_instances_binder::binder_name ()
{
	return ::std::wstring (L"routine_instances_binder");
}