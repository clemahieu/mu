#include "group.h"

#include <lambda_p/binder/routine_instances.h>

void lambda_p::binder::group::bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances_a, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	for (::std::vector < ::boost::shared_ptr < ::lambda_p::binder::instance> >::iterator i = instances_a.instances.begin () ; i != instances_a.instances.end (); ++i)
	{
		instances.push_back (*i);
	}
}

::std::wstring lambda_p::binder::group::binder_name ()
{
	return ::std::wstring (L"group_binder");
}