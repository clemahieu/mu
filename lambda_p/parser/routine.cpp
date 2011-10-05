#include <lambda_p/parser/routine.h>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>

lambda_p::parser::routine::routine(void)
	: parsed_routine (false),
	routine_m (new ::lambda_p::core::routine),
	have_surface (false)
{
}

lambda_p::parser::routine::~routine(void)
{
}

::lambda_p::parser::state_id lambda_p::parser::routine::state_type ()
{
	return ::lambda_p::parser::state_routine;
}

void lambda_p::parser::routine::sink_result (size_t declaration)
{
	routine_m->surface->results.push_back (declaration);
}

void lambda_p::parser::routine::sink_argument (size_t argument)
{
	routine_m->surface->parameters.push_back (argument);
}