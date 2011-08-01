#include <lambda_p/core/statement.h>

::lambda_p::core::statement::statement (::std::string name_a, ::boost::shared_ptr < ::lambda_p::core::node> target_a)
	: name (new ::lambda_p::core::node (name_a)),
	target (target_a)
{
}

::lambda_p::core::statement::~statement (void)
{
}