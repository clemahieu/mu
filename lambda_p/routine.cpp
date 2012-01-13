#include "routine.h"

#include <lambda_p/set.h>

lambda_p::routine::routine ()
	: parameters (new lambda_p::set),
	body (new lambda_p::set)
{
}