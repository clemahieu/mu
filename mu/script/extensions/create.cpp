#include "create.h"

#include <mu/script/extensions/node.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

void mu::script::extensions::create::operator () (mu::script::context & context_a)
{
	if (mu::script::check <> () (context_a))
	{
		context_a.results.push_back (boost::make_shared <mu::script::extensions::node> ());
	}
}

size_t mu::script::extensions::create::count ()
{
	return 0;
}