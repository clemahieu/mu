#include "create_get.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/load/operation.h>
#include <mu/script/closure/single.h>
#include <mu/script/cluster/get_named.h>

#include <boost/make_shared.hpp>

mu::script::load::create_get::create_get (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: extensions (extensions_a)
{
}

void mu::script::load::create_get::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	mu::script::load::operation load (extensions);
	std::vector <boost::shared_ptr <mu::core::node>> results_l;
	load (errors_a, parameters, results_l);
	if (!(*errors_a) ())
	{
		auto result (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::script::cluster::get_named> ()));
		result->closed.push_back (results_l [0]);
		results.push_back (result);
	}
}

size_t mu::script::load::create_get::count ()
{
	return 1;
}