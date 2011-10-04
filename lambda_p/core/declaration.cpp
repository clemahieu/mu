#include <lambda_p/core/declaration.h>

#include <iostream>

#include <lambda_p/core/routine.h>

lambda_p::core::declaration::declaration ()
{
}

lambda_p::core::declaration::~declaration (void)
{
}

::lambda_p::core::node_id lambda_p::core::declaration::node_type () const
{
	return ::lambda_p::core::node_declaration;
}