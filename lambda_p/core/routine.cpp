#include <lambda_p/core/routine.h>

#include <lambda_p/core/expression_list.h>

lambda_p::core::routine::routine ()
	: expression (new lambda_p::core::expression_list)
{
}