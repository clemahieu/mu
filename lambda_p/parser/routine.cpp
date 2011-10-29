#include <lambda_p/parser/routine.h>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list_binder.h>
#include <lambda_p/parser/position_set.h>

#include <boost/bind.hpp>

lambda_p::parser::routine::routine(void)
	: parsed_routine (false),
	routine_m (new lambda_p::core::routine),
	have_surface (false)
{
	//size_t list_position (routine_m->add_declaration ());
	//routine_m->surface->results.push_back (list_position);
	//positions [std::wstring (L"~")] = list_position;
	//routine_m->nodes [list_position] = boost::shared_ptr <lambda_p::binder::list_binder> (new lambda_p::binder::list_binder);
}

lambda_p::parser::routine::~routine(void)
{
}

lambda_p::parser::state_id lambda_p::parser::routine::state_type ()
{
	return lambda_p::parser::state_routine;
}

boost::function <void (size_t)> lambda_p::parser::routine::sink_declaration ()
{
	routine_m->surface->declarations.push_back (~0);
	boost::function <void (size_t)> result (boost::bind <void> (lambda_p::parser::position_set (routine_m->surface->declarations, routine_m->surface->declarations.size () - 1), _1));
	return result;
}

boost::function <void (size_t)> lambda_p::parser::routine::sink_argument ()
{
	routine_m->surface->references.push_back (~0);
	boost::function <void (size_t)> result (boost::bind <void> (lambda_p::parser::position_set (routine_m->surface->references, routine_m->surface->references.size () - 1), _1));
	return result;
}