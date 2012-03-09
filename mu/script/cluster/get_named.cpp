#include "get_named.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/cluster/node.h>
#include <mu/script/string/node.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/check.h>

#include <sstream>

void mu::script::cluster::get_named::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::cluster::node, mu::script::string::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::script::cluster::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters [1]));
		auto existing (one->names.find (two->string));
		if (existing != one->names.end ())
		{
			context_a.results.push_back (existing->second);
		}
		else
		{
			std::wstringstream message;
			message << L"Unable to get routine named: ";
			message << two->string;
			(*context_a.errors) (message.str ());
		}
	}
}
	
size_t mu::script::cluster::get_named::count ()
{
	return 2;
}