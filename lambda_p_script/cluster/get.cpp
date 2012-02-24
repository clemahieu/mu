#include "get.h"

#include <mu/core/routine.h>
#include <lambda_p_script/cluster/node.h>
#include <lambda_p_script/routine.h>
#include <mu/core/errors/error_target.h>

void lambda_p_script::cluster::get::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_script::cluster::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::core::routine> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto existing (one->mapping.find (two));
			if (existing != one->mapping.end ())
			{
				results.push_back (existing->second);
			}
			else
			{
				(*errors_a) (L"Cluster has no mapping for routine");
			}
		}
		else
		{
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_script::cluster::get::count ()
{
	return 2;
}