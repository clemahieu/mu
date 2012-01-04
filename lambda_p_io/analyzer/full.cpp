#include "full.h"

#include <lambda_p/tee.h>

lambda_p_io::analyzer::full::full (boost::shared_ptr <lambda_p::tee> tee_a)
	: tee (tee_a)
{
	assert (tee.get () != nullptr);
}

void lambda_p_io::analyzer::full::operator () (boost::shared_ptr <lambda_p::target> target_a)
{
	tee->targets.push_back (target_a);
}