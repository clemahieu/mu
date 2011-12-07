#include "list.h"

#include <lambda_p/binder/list.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/errors/string_error.h>
#include <lambda_p/core/expression.h>

#include <sstream>

void lambda_p::binder::list::bind (lambda_p::core::expression * expression, std::map <lambda_p::core::expression *, boost::shared_ptr <lambda_p::binder::node>> & nodes_a, lambda_p::errors::error_list & problems)
{
	//if (expression->begin () == expression->end ())
	//{
	//	std::vector <boost::shared_ptr <lambda_p::binder::node>>::iterator j = nodes.begin ();
	//	for (std::vector <size_t>::iterator i = statement->association->declarations.begin (); i != statement->association->declarations.end (); ++i, ++j)
	//	{
	//		nodes_a [*i] = *j;
	//	}
	//}
	//else
	//{
	//	add_error (std::wstring (L"Not expecting arguments"), problems);
	//}
}

boost::shared_ptr <lambda_p::binder::node> & lambda_p::binder::list::operator [] (size_t node)
{
	if (node >= nodes.size ())
	{
		nodes.resize (node + 1);
	}
	boost::shared_ptr <lambda_p::binder::node> & result (nodes [node]);
	return result;
}

void lambda_p::binder::list::merge (lambda_p::binder::list & other_a, lambda_p::errors::error_list & problems)
{
	nodes.resize (std::max (nodes.size (), other_a.nodes.size ()));
	size_t position (0);
	auto self (nodes.begin ());
	auto other (other_a.nodes.begin ());
	while (other != other_a.nodes.end ())
	{
		auto val (*other);
		if (val.get () != nullptr)
		{
			if (self->get () != nullptr)
			{
				std::wstringstream message;
				message << L"Both instance containers have an instance at index: ";
				message << position;
				problems (new lambda_p::errors::string_error (message.str ()));
			}
			else
			{
				*self = val;
			}
		}
		++self;
		++other;
		++position;
	}
}

std::wstring lambda_p::binder::list::binder_name ()
{
	return std::wstring (L"list");
}