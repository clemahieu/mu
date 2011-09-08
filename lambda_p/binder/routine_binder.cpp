#include "routine_binder.h"

#include <lambda_p/core/routine.h>

lambda_p::binder::routine_binder::routine_binder(::std::map < ::lambda_p::core::node *, ::lambda_p::binder::node_binder *> binders_a)
	: binders (binders_a)
{
}

lambda_p::binder::routine_binder::~routine_binder(void)
{
}

void lambda_p::binder::routine_binder::bind (::lambda_p::core::routine * routine_a)
{
	for (::std::vector < ::lambda_p::core::statement *>::iterator i = routine_a->statements.begin (); i != routine_a->statements.end (); ++i)
	{
		if (arguments_resolved (*i))
		{

		}
		else
		{

		}
	}
}

bool lambda_p::binder::routine_binder::arguments_resolved (::lambda_p::core::statement * statement)
{
	return false;
}