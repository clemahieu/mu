#include "null_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>

lambda_p::binder::null_binder::null_binder(void)
{
}

lambda_p::binder::null_binder::~null_binder(void)
{
}

void lambda_p::binder::null_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	for (::std::vector < ::lambda_p::core::node *>::iterator i = statement->association->results.begin (); i != statement->association->results.end (); ++i)
	{
		instances [*i] = ::boost::shared_ptr < ::lambda_p::binder::node_instance> (new ::lambda_p::binder::null_binder);
	}
}

::std::wstring lambda_p::binder::null_binder::binder_name ()
{
	return ::std::wstring (L"null_binder");
}