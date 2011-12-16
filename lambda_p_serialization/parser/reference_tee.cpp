#include "reference_tee.h"

#include <lambda_p/core/tee.h>

lambda_p_serialization::parser::reference_tee::reference_tee (boost::shared_ptr <lambda_p::core::tee> tee_a)
	: tee (tee_a)
{
}

void lambda_p_serialization::parser::reference_tee::operator () (boost::shared_ptr <lambda_p::core::target> target_a)
{
	tee->targets.push_back (target_a);
}