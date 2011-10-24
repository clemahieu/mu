#include "routine_instances_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unexpected_result_count.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p/binder/list.h>

lambda_p::binder::routine_instances_binder::routine_instances_binder(void)
{
}

void lambda_p::binder::routine_instances_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.empty ())
	{
		boost::shared_ptr <lambda_p::binder::list> list (boost::dynamic_pointer_cast <lambda_p::binder::list> (instances [statement->association->parameters [0]]));
		if (list.get () != NULL)
		{
			boost::shared_ptr < lambda_p::binder::routine_instances> instances_l (new lambda_p::binder::routine_instances);
			for (std::vector < boost::shared_ptr < lambda_p::binder::instance> >::iterator i = list->instances.begin (); i != list->instances.end (); ++i)
			{
				instances_l->instances.push_back (*i);
				instances [statement->association->results [0]] = instances_l;
			}
		}
		else
		{
			unexpected_binder_type_error (0, std::wstring (L"list"), problems);
		}
	}
}

std::wstring lambda_p::binder::routine_instances_binder::binder_name ()
{
	return std::wstring (L"routine_instances_binder");
}