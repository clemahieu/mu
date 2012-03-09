#include "synthesizer.h"

#include <mu/core/order.h>
#include <mu/core/routine.h>
#include <mu/core/cluster.h>
#include <mu/script_io/routine.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/cluster/node.h>
#include <mu/script_io/cluster.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

void mu::script_io::synthesizer::operator() (mu::script::context & context_a)
{
	if (mu::script::check <mu::core::cluster> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::core::cluster> (context_a.parameters [0]));
		mu::script_io::cluster cluster (one);
		if (cluster.result.get () != nullptr)
		{
			context_a.results.push_back (cluster.result);
		}
	}
}

std::wstring mu::script_io::synthesizer::name ()
{
	return std::wstring (L"mu::script_io::synthesizer");
}