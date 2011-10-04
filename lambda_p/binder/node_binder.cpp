#include "node_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>

#include <sstream>

lambda_p::binder::node_binder::node_binder(void)
{
}

lambda_p::binder::node_binder::~node_binder(void)
{
}

void lambda_p::binder::node_binder::check_count_only_references (bool & problem, size_t result_count, size_t argument_count, wchar_t const * binder_name, ::lambda_p::core::statement * statement, ::std::wstringstream & problems)
{
	check_count (problem, result_count, argument_count, binder_name, statement, problems);
	check_only_references (problem, binder_name, statement, problems);
}

void lambda_p::binder::node_binder::check_only_references (bool & problem, wchar_t const * binder_name, ::lambda_p::core::statement * statement, ::std::wstringstream & problems)
{
	size_t position (1);
	for (::std::vector < ::lambda_p::core::node *>::iterator i = statement->parameters.begin (); i != statement->parameters.end (); ++i, ++position)
	{
		::lambda_p::core::node_id type ((*i)->node_type ());
		switch (type)
		{
		case ::lambda_p::core::node_reference:
				// Reference is what we're looking for
			break;
		case ::lambda_p::core::node_data:
				problem = true;
				problems << binder_name;
				problems << L" is not expecting data as argument number: ";
				problems << position;
				problems << L'\n';
			break;
		default:
			// Should only have references or data at this point
			problem = true;
			assert (false);
			break;
		}
	}
}

void lambda_p::binder::node_binder::check_count (bool & problem, size_t result_count, size_t argument_count, wchar_t const * binder_name, ::lambda_p::core::statement * statement, ::std::wstringstream & problems)
{
	if (statement->results.size () != result_count)
	{
		problem = true;
		problems << binder_name;
		problems << L" is expecting ";
		problems << result_count;
		problems << L" results, have; ";
		problems << statement->results.size ();
		problems << L'\n';
	}
	if (statement->parameters.size () != argument_count)
	{
		problem = true;
		problems << binder_name;
		problems << L" is expecting ";
		problems << argument_count;
		problems << L" arguments, have: ";
		problems << statement->parameters.size ();
		problems << L'\n';
	}
}