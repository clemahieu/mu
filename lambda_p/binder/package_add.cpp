#include "package_add.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p/binder/package.h>
#include <lambda_p/binder/data.h>

void lambda_p::binder::package_add::bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (0, 3, statement, problems);
	if (problems.empty ())
	{
		::boost::shared_ptr < ::lambda_p::binder::package> package (::boost::dynamic_pointer_cast < ::lambda_p::binder::package> (instances [statement->association->parameters [0]]));
		if (package.get () != NULL)
		{
			::boost::shared_ptr < ::lambda_p::binder::data> data (::boost::dynamic_pointer_cast < ::lambda_p::binder::data> (instances [statement->association->parameters [2]]));
			if (data.get () != NULL)
			{
				package->nodes [data->string ()] = instances [statement->association->parameters [1]];
			}
			else
			{
				unexpected_binder_type_error (2, ::std::wstring (L"data"), problems);
			}
		}
		else
		{
			unexpected_binder_type_error (0, ::std::wstring (L"package"), problems);
		}
	}
}

::std::wstring lambda_p::binder::package_add::binder_name ()
{
	return ::std::wstring (L"package_add");
}