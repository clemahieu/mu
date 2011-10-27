#include "routine_instances.h"

#include <lambda_p/errors/string_error.h>
#include <lambda_p/errors/error_list.h>

#include <sstream>

lambda_p::binder::routine_instances::routine_instances(void)
{
}

boost::shared_ptr < lambda_p::binder::instance> & lambda_p::binder::routine_instances::operator [] (size_t node)
{
	if (node >= instances.size ())
	{
		instances.resize (node + 1);
	}
	boost::shared_ptr < lambda_p::binder::instance> & result (instances [node]);
	return result;
}

void lambda_p::binder::routine_instances::merge (routine_instances & other_a, lambda_p::errors::error_list & problems)
{
	instances.resize (std::max (instances.size (), other_a.instances.size ()));
	size_t position (0);
	auto self (instances.begin ());
	auto other (other_a.instances.begin ());
	while (other != other_a.instances.end ())
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