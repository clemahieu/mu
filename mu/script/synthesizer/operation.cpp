#include <mu/script/synthesizer/operation.h>

#include <mu/script/context.h>
#include <mu/script/check.h>
#include <mu/core/cluster.h>

bool mu::script::synthesizer::operation::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::core::cluster> () (context_a));
	if (valid)
	{
	}
	return valid;
}