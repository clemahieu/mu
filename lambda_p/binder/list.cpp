#include "list.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/node_list.h>
#include <sstream>

void lambda_p::binder::list::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes_a, lambda_p::errors::error_list & problems)
{
	if (statement->association->references.empty ())
	{
		if (statement->association->declarations.size () == nodes.size ())
		{
			std::vector <boost::shared_ptr <lambda_p::binder::node>>::iterator j = nodes.begin ();
			for (std::vector <size_t>::iterator i = statement->association->declarations.begin (); i != statement->association->declarations.end (); ++i, ++j)
			{
				nodes_a [*i] = *j;
			}
		}
		else
		{
			std::wstringstream message;
			message << L"Unexpected number of declarations, have: ";
			message << statement->association->declarations.size ();
			message < L" expecting: ";
			message << nodes.size ();
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