#include "remap.h"

#include <mu/script/runtime/context.h>
#include <mu/core/routine.h>
#include <mu/script/cluster/node.h>
#include <mu/core/errors/error_target.h>
#include <mu/core/expression.h>

mu::script::runtime::remap::remap (boost::shared_ptr <mu::core::routine> routine_a)
	: routine (routine_a)
{
}

void mu::script::runtime::remap::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::script::runtime::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target)
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