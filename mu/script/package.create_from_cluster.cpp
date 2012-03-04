#include <mu/script/package.create_from_cluster.h>

#include <mu/script/cluster.node.h>
#include <mu/script/package.node.h>
#include <mu/script/runtime.routine.h>

#include <boost/make_shared.hpp>

void mu::script::package::create_from_cluster::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::cluster::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		auto result (boost::make_shared <mu::script::package::node> ());
		for (auto i (one->names.begin ()), j (one->names.end ()); i != j; ++i)
		{
			result->items [i->first] = i->second;
		}
		results.push_back (result);
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::script::package::create_from_cluster::count ()
{
	return 1;
}
