#include <lambda_p/core/statement.h>

::lambda_p::core::statement::statement (::lambda_p::core::identifier * declaration_a, ::lambda_p::core::identifier * target_a)
	: declaration (declaration_a),
	target (target_a)
{
}

::lambda_p::core::statement::~statement (void)
{
}