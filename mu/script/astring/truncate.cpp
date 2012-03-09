#include "truncate.h"

#include <mu/script/string/node.h>
#include <mu/script/astring/node.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

void mu::script::astring::truncate::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::string::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters [0]));
		std::string string (one->string.begin (), one->string.end ());
		context_a.results.push_back (boost::make_shared <mu::script::astring::node> (string));
	}
}

size_t mu::script::astring::truncate::count ()
{
	return 1;
}