#include "fixed.h"

#include <lambda_p/core/tee.h>

lambda_p::core::fixed::fixed ()
	: target (new lambda_p::core::tee)
{
}

void lambda_p::core::fixed::operator () ()
{
	(*target) (arguments);
}