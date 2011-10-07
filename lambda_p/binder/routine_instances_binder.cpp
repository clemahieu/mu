#include "routine_instances_binder.h"

lambda_p::binder::routine_instances_binder::routine_instances_binder(void)
{
}

void lambda_p::binder::routine_instances_binder::bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{

}

::std::wstring lambda_p::binder::routine_instances_binder::binder_name ()
{
	return ::std::wstring (L"routine_instances_binder");
}