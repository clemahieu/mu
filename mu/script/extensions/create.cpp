#include <mu/script/extensions/create.h>

#include <mu/script/extensions/node.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

bool mu::script::extensions::create::operator () (mu::script_runtime::context & context_a)
{
	bool result (mu::script::check <> () (context_a));
	if (result)
	{
		context_a.push (boost::make_shared <mu::script::extensions::node> ());
	}
	return result;
}