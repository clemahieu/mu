#include <lambda_p/parser/routine.h>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list_binder.h>

lambda_p::parser::routine::routine(void)
	: parsed_routine (false),
	routine_m (new lambda_p::core::routine),
	have_surface (false)
{
	size_t list_position (routine_m->add_declaration ());
	routine_m->surface->results.push_back (list_position);
	positions [std::wstring (L"~")] = list_position;
	routine_m->instances [list_position] = boost::shared_ptr <lambda_p::binder::list_binder> (new lambda_p::binder::list_binder);
}

lambda_p::parser::routine::~routine(void)
{
}

lambda_p::parser::state_id lambda_p::parser::routine::state_type ()
{
	return lambda_p::parser::state_routine;
}

void lambda_p::parser::routine::sink_result (size_t * & declaration)
{
	routine_m->surface->results.push_back (~0);
	declaration = &routine_m->surface->results [routine_m->surface->results.size () - 1];
}

void lambda_p::parser::routine::sink_argument (size_t * & argument)
{
	routine_m->surface->parameters.push_back (~0);
	argument = & (routine_m->surface->parameters [routine_m->surface->parameters.size () - 1]);
}