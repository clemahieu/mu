#include "node_list.h"

#include <lambda_p/errors/string_error.h>
#include <lambda_p/errors/error_list.h>

#include <sstream>

lambda_p::binder::node_list::node_list(void)
{
}

boost::shared_ptr <lambda_p::binder::node> & lambda_p::binder::node_list::operator [] (size_t node)
{
	if (node >= nodes.size ())
	{
		nodes.resize (node + 1);
	}
	boost::shared_ptr < lambda_p::binder::node> & result (nodes [node]);
	return result;
}

void lambda_p::binder::node_list::merge (node_list & other_a, lambda_p::errors::error_list & problems)
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