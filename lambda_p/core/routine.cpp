#include <lambda_p/core/routine.h>

lambda_p::core::routine::routine(::std::string name_a)
	: body (new ::lambda_p::core::body),
	name (name_a)
{
}

lambda_p::core::routine::~routine(void)
{
}