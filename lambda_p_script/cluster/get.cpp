#include "get.h"

#include <lambda_p/routine.h>
#include <lambda_p_script/cluster/node.h>
#include <lambda_p_script/routine.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/remapping.h>

void lambda_p_script::cluster::get::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_script::cluster::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p::routine> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto existing (one->remapping->generated.find (two));
			if (existing != one->remapping->generated.end ())
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