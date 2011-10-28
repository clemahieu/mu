#include "list.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/routine_instances.h>
#include <sstream>

void lambda_p::binder::list::bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances_a, lambda_p::errors::error_list & problems)
{
	if (statement->association->parameters.empty ())
	{
		if (statement->association->results.size () == instances.size ())
		{
			std::vector <boost::shared_ptr < lambda_p::binder::node>>::iterator j = instances.begin ();
			for (std::vector <size_t>::iterator i = statement->association->results.begin (); i != statement->association->results.end (); ++i, ++j)
			{
				instances_a [*i] = *j;
			}
		}
		else
		{
			std::wstringstream message;
			message << L"Unexpected number of results, have: ";
			message << statement->association->results.size ();
			message < L" expecting: ";
			message << instances.size ();
			add_error (message.str (), problems);
		}
	}
	else
	{
		add_error (std::wstring (L"Not expecting parameters"), problems);
	}
}

std::wstring lambda_p::binder::list::binder_name ()
{
	return std::wstring (L"list");
}