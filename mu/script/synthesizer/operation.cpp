#include <mu/script/synthesizer/operation.h>

#include <mu/script/context.h>
#include <mu/script/check.h>
#include <mu/script/synthesizer/operationd.h>
#include <mu/core/cluster.h>
#include <mu/io/debugging/mapping.h>
#include <mu/io/debugging/stream.h>

#include <boost/make_shared.hpp>

bool mu::script::synthesizer::operation::operator () (mu::script::context & context_a)
{
	auto valid (mu::script::check <mu::core::cluster> () (context_a));
	if (valid)
	{
		context_a.push (boost::make_shared <mu::script::synthesizer::operationd> ());
		context_a.push (context_a.parameters (0));
		context_a.push (boost::make_shared <mu::io::debugging::mapping> (boost::make_shared <mu::io::debugging::stream> ()));
		valid = context_a ();
		if (valid)
		{
			context_a.stack.resize (context_a.stack.size () - 1);
		}
	}
	return valid;
}