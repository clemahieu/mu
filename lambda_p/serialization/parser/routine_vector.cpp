#include "routine_vector.h"

lambda_p::serialization::parser::routine_vector::routine_vector(void)
{
}

lambda_p::serialization::parser::routine_vector::~routine_vector(void)
{
}
				
void lambda_p::serialization::parser::routine_vector::operator () (::boost::shared_ptr < ::lambda_p::core::routine> routine)
{
	routines.push_back (routine);
}
