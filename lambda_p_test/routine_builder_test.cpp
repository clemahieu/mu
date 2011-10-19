#include "routine_builder_test.h"

#include <lambda_p/routine_builder.h>

void lambda_p_test::routine_builder_test::run ()
{	
	lambda_p::routine_builder routine;
	routine (L"add a b c = result; add res = a b; add result = res c; #;");
	assert (routine.routines.routines->size () == 1);
}