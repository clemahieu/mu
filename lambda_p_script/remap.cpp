#include "remap.h"

#include <lambda_p_script/context.h>
#include <lambda_p/routine.h>
#include <lambda_p_script/cluster/node.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p/expression.h>

lambda_p_script::remap::remap (boost::shared_ptr <lambda_p::routine> routine_a)
	: routine (routine_a)
{
}

void lambda_p_script::remap::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::context & context, std::vector <boost::shared_ptr <lambda_p::node>> & target)
{
	auto existing (context.cluster->mapping.find (routine));
	if (existing != context.cluster->mapping.end ())
	{
		target.push_back (existing->second);
	}
	else
	{
		(*errors_a) (L"Routine is no longer mapped", routine->body->context);
	}
}