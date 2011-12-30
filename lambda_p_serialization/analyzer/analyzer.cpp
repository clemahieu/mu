#include "analyzer.h"

lambda_p_serialization::analyzer::analyzer::analyzer (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a)
	: target (target_a)
{
}

void lambda_p_serialization::analyzer::analyzer::operator () (boost::shared_ptr <lambda_p_serialization::ast::node> node)
{
}