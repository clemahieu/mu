#include <lambda_p/core/statement.h>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>

lambda_p::core::statement::statement ()
	: association (new lambda_p::core::association)
{
}

lambda_p::core::statement::~statement (void)
{
}