#include "remap.h"

#include <lambda_p_script/context.h>
#include <lambda_p_script/remapping.h>
#include <lambda_p/routine.h>

lambda_p_script::remap::remap (boost::shared_ptr <lambda_p::routine> routine_a)
	: routine (routine_a)
{
}

void lambda_p_script::remap::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::context & context, std::vector <boost::shared_ptr <lambda_p::node>> & target)
{
	auto existing (context.remapping->generated.find (routine));
	assert (existing != context.remapping->generated.end ());
	target.push_back (existing->second);
}