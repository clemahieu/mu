#include "routine_vector.h"

lambda_p::parser::routine_vector::routine_vector(void)
	: routines (new ::std::vector < ::boost::shared_ptr < ::lambda_p::core::routine> >)
{
}

lambda_p::parser::routine_vector::~routine_vector(void)
{
}
				
void lambda_p::parser::routine_vector::operator () (::boost::shared_ptr < ::lambda_p::core::routine> routine)
{
	routines->push_back (routine);
}
