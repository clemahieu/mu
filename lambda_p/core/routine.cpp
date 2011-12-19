#include "routine.h"

#include <lambda_p/core/pipe.h>
#include <lambda_p/errors/error_list.h>

lambda_p::core::routine::routine ()
	: output (new lambda_p::core::pipe),
	errors (new lambda_p::errors::error_list)
{
}
