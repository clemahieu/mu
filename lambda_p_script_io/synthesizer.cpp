#include "synthesizer.h"

#include <core/order.h>
#include <core/routine.h>
#include <core/cluster.h>
#include <lambda_p_script_io/routine.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script/cluster/node.h>
#include <lambda_p_script_io/cluster.h>

#include <boost/make_shared.hpp>

void lambda_p_script_io::synthesizer::operator() (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::core::cluster> (parameters [0]));
	if (one.get () != nullptr)
	{
		lambda_p_script_io::cluster cluster (one);
		if (cluster.result.get () != nullptr)
		{
			results.push_back (cluster.result);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_script_io::synthesizer::count ()
{
	return 1;
}

std::wstring lambda_p_script_io::synthesizer::name ()
{
	return std::wstring (L"lambda_p_script_io::synthesizer");
}