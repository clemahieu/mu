#include "create_from_cluster.h"

#include <mu/script/cluster/node.h>
#include <mu/script/package/node.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

void mu::script::package::create_from_cluster::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::cluster::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::script::cluster::node> (context_a.parameters [0]));
		auto result (boost::make_shared <mu::script::package::node> ());
		for (auto i (one->names.begin ()), j (one->names.end ()); i != j; ++i)
		{
			result->items [i->first] = i->second;
		}
		context_a.results.push_back (result);
	}
}

size_t mu::script::package::create_from_cluster::count ()
{
	return 1;
}