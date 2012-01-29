#include "cluster.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/string/node.h>
#include <lambda_p_script/integer/node.h>
#include <lambda_p_script/routine.h>

#include <sstream>

lambda_p_script::cluster::cluster (std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a)
	: routines (routines_a)
{
}

lambda_p_script::cluster::cluster (std::map <std::wstring, size_t> names_a, std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a)
	: names (names_a),
	routines (routines_a)
{
}

void lambda_p_script::cluster::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_script::string::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		auto existing (names.find (one->string));
		if (existing != names.end ())
		{
			results.push_back (routines [existing->second]);
		}
		else
		{
			std::wstringstream message;
			message << L"Cluster does not contain routine named: ";
			message << one->string;
			(*errors_a) (message.str ());
		}
	}
	else
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_script::integer::node> (parameters [0]));
		if (one.get () != nullptr)
		{
			if (routines.size () > one->value)
			{
				results.push_back (routines [one->value]);
			}
			else
			{
				std::wstringstream message;
				message << L"Cluster does not have a rounite numbered: ";
				message << one->value;
				(*errors_a) (message.str ());
			}
		}
		else
		{
			invalid_type (errors_a, parameters [0], 0);
		}
	}
}

size_t lambda_p_script::cluster::count ()
{
	return 1;
}