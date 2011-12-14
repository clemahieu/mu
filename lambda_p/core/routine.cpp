#include "routine.h"

#include <lambda_p/core/pipe.h>

lambda_p::core::routine::routine ()
	: output (new lambda_p::core::pipe)
{
}
