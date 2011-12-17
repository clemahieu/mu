#include "routine_vector.h"

lambda_p_serialization::parser::routine_vector::routine_vector ()
	: routines (new std::vector <boost::shared_ptr <lambda_p::core::routine>>)
{
}
				
void lambda_p_serialization::parser::routine_vector::operator () (boost::shared_ptr <lambda_p::core::routine> routine)
{
	routines->push_back (routine);
}
