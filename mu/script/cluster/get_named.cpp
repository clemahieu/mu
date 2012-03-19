#include <mu/script/cluster/get_named.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/cluster/node.h>
#include <mu/script/string/node.h>
#include <mu/script/check.h>

#include <sstream>

bool mu::script::cluster::get_named::operator () (mu::script_runtime::context & context_a)
{
	bool result (mu::script::check <mu::script::cluster::node, mu::script::string::node> () (context_a));
	if (result)
	{
		auto one (boost::static_pointer_cast <mu::script::cluster::node> (context_a.parameters (0)));
		auto two (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters (1)));
		auto existing (one->names.find (two->string));
		if (existing != one->names.end ())
		{
			context_a.push (existing->second);
		}
		else
		{
			std::wstringstream message;
			message << L"Unable to get routine named: ";
			message << two->string;
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}