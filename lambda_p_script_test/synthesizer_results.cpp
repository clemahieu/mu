#include "synthesizer_results.h"

void lambda_p_script_test::synthesizer_results::operator () (boost::shared_ptr <lambda_p_script::runtime::routine> routine_a)
{
	routines.push_back (routine_a);
}