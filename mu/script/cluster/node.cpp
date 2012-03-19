#include <mu/script/cluster/node.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/script/integer/node.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>
#include <mu/script/check.h>

#include <sstream>
#include <set>

mu::script::cluster::node::node ()
{
}

mu::script::cluster::node::node (std::vector <boost::shared_ptr <mu::script::runtime::routine>> routines_a)
	: routines (routines_a)
{
}

mu::script::cluster::node::node (std::map <std::wstring, boost::shared_ptr <mu::script::runtime::routine>> names_a, std::vector <boost::shared_ptr <mu::script::runtime::routine>> routines_a)
	: names (names_a),
	routines (routines_a)
{
}

bool mu::script::cluster::node::operator () (mu::script_runtime::context & context_a)
{
	bool result (mu::script::check <mu::script::string::node> () (context_a));
	if (result)
	{
		auto one (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters (0)));
		auto existing (names.find (one->string));
		if (existing != names.end ())
		{
			context_a.push (existing->second);
		}
		else
		{
			std::wstringstream message;
			message << L"Cluster does not contain routine named: ";
			message << one->string;
			context_a.errors (message.str ());
			result = false;
		}
	}
	else
	{
		if (mu::script::check <mu::script::integer::node> () (context_a))
		{
			auto one (boost::static_pointer_cast <mu::script::integer::node> (context_a.parameters (0)));
			if (routines.size () > one->value)
			{
				context_a.push (routines [one->value]);
			}
			else
			{
				std::wstringstream message;
				message << L"Cluster does not have a rounite numbered: ";
				message << one->value;
				context_a.errors (message.str ());
				result = false;
			}
		}
	}
	return result;
}