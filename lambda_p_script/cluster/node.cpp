#include "node.h"

#include <mu/core/errors/error_target.h>
#include <lambda_p_script/string/node.h>
#include <lambda_p_script/integer/node.h>
#include <lambda_p_script/routine.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>

#include <sstream>
#include <set>

lambda_p_script::cluster::node::node ()
{
}

lambda_p_script::cluster::node::node (std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a, std::map <boost::shared_ptr <mu::core::routine>, boost::shared_ptr <mu::core::node>> mapping_a)
	: routines (routines_a),
	mapping (mapping_a)
{
}

lambda_p_script::cluster::node::node (std::map <std::wstring, boost::shared_ptr <mu::core::routine>> names_a, std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a, std::map <boost::shared_ptr <mu::core::routine>, boost::shared_ptr <mu::core::node>> mapping_a)
	: names (names_a),
	routines (routines_a),
	mapping (mapping_a)
{
}

void lambda_p_script::cluster::node::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_script::string::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		auto existing (names.find (one->string));
		if (existing != names.end ())
		{
			results.push_back (mapping [existing->second]);
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

size_t lambda_p_script::cluster::node::count ()
{
	return 1;
}

void lambda_p_script::cluster::node::remap (std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> & remap_a)
{
	std::set <boost::shared_ptr <mu::core::routine>> unmapped;
	for (auto i (mapping.begin ()), j (mapping.end ()); i != j; ++i)
	{
		auto new_l (remap_a.find (i->second));
		if (new_l == remap_a.end ())
		{
			unmapped.insert (i->first);
		}
		else
		{
			i->second = new_l->second;
		}
	}
	for (auto i (unmapped.begin ()), j (unmapped.end ()); i != j; ++i)
	{
		mapping.erase (*i);
	}
}