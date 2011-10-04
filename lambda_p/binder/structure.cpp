#include "structure.h"

#include <lambda_p/core/declaration.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/data.h>
#include <lambda_p/core/reference.h>

#include <sstream>

lambda_p::binder::structure::structure(void)
{
}

lambda_p::binder::structure::~structure(void)
{
}

void lambda_p::binder::structure::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	bool problem (false);
	check_count (problem, 1, 1, L"structure_binder", statement, problems);
	if (!problem)
	{
		::lambda_p::core::node_id argument_1_id (statement->parameters [0]->node_type ());
		switch (argument_1_id)
		{
		case ::lambda_p::core::node_data:
			{
				::lambda_p::core::data * name (static_cast < ::lambda_p::core::data *> (statement->parameters [0]));
				::std::map < ::std::wstring, ::boost::shared_ptr < ::lambda_p::binder::node_instance> >::iterator target = nodes.find (name->string ());
				if (target != nodes.end ())
				{
					instances [statement->results [0]] = target->second;
				}
				else
				{
					problems << L"Structure has no member named: ";
					problems << name->string ();
					problems << '\n';
				}
			}
			break;
		default:
			problems << L"dereference is expecting argument 1 to be data, have: ";
			problems << statement->parameters [0]->node_type_name ();
			problems << '\n';
			break;
		}
	}
}