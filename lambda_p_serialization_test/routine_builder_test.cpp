#include "routine_builder_test.h"

#include <lambda_p_serialization/builder.h>

void lambda_p_serialization_test::routine_builder_test::run ()
{	
	lambda_p_serialization::builder routine;
	routine (L"[] []");
	assert (routine.routines.routines->size () == 1);
}