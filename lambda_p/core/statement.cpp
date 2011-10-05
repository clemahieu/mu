#include <lambda_p/core/statement.h>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>

lambda_p::core::statement::statement (size_t target_a)
	: target (target_a),
	association (new ::lambda_p::core::association)
{
}

lambda_p::core::statement::~statement (void)
{
}