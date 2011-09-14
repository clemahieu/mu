#include "command_list.h"

#include <lambda_p/binder/node_instance.h>

lambda_p::binder::command_list::command_list(void)
{
}

lambda_p::binder::command_list::~command_list(void)
{
}

void lambda_p::binder::command_list::operator () ()
{
	for (::std::vector < ::lambda_p::binder::node_instance *>::iterator i = instances.begin (); i != instances.end (); ++i)
	{
		(**i) ();
	}
}

void lambda_p::binder::command_list::add_instance (::lambda_p::binder::node_instance * instance)
{
	instances.push_back (instance);
}