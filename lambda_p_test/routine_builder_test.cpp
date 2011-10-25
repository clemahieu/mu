#include "routine_builder_test.h"

#include <lambda_p/routine_builder.h>

void lambda_p_test::routine_builder_test::run ()
{	
	lambda_p::routine_builder routine;
	routine (L"result; add a b c; add a b; res; add res c; result; :;");
	assert (routine.routines.routines->size () == 1);
}