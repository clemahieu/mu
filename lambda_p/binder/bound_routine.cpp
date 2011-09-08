#include "bound_routine.h"

#include <lambda_p/binder/node_instance.h>

lambda_p::binder::bound_routine::bound_routine(void)
{
}

lambda_p::binder::bound_routine::~bound_routine(void)
{
}

void lambda_p::binder::bound_routine::operator () ()
{
	for (::std::vector < ::lambda_p::binder::node_instance *>::iterator i = instances.begin (); i != instances.end (); ++i)
	{
		(**i) ();
	}
}

void lambda_p::binder::bound_routine::add_instance (::lambda_p::binder::node_instance * instance)
{
	instances.push_back (instance);
}