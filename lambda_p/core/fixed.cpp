#include "fixed.h"

#include <lambda_p/core/target.h>

void lambda_p::core::fixed::operator () ()
{
	(*target) (arguments);
}