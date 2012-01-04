#include "fixed.h"

#include <lambda_p/tee.h>

lambda_p::fixed::fixed ()
	: target (new lambda_p::tee)
{
}

void lambda_p::fixed::operator () ()
{
	(*target) (arguments);
}