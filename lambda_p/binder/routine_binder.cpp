#include "routine_binder.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/binder/node_binder.h>

#include <sstream>

lambda_p::binder::routine_binder::routine_binder ()
{
}

lambda_p::binder::routine_binder::~routine_binder(void)
{
}

void lambda_p::binder::routine_binder::operator () (::boost::shared_ptr < ::lambda_p::core::routine> routine_a)
{
	::std::vector < ::lambda_p::core::statement *>::iterator i = routine_a->statements.begin ();
	assert (i != routine_a->statements.end ()); // No first statement means a routine with no parameters
	++i; // Skip first statement, the parameters
	while (i != routine_a->statements.end ())
	{
		::lambda_p::core::statement * statement (*i);	
		bind_statement (routine_a, statement);
		++i;
	}
	for (::std::map < ::lambda_p::core::node *, ::lambda_p::core::statement *>::iterator i = unbound_statements.begin (); i != unbound_statements.end (); ++i)
	{
		error_message_m << L"Unresolved node\n";
	}
}

void lambda_p::binder::routine_binder::bind_statement (::boost::shared_ptr < ::lambda_p::core::routine> routine_a, ::lambda_p::core::statement * statement)
{	
	::boost::shared_ptr < ::lambda_p::binder::node_binder> binder;
	populate_unbound (routine_a, statement, binder);
	if (binder.get () != NULL)
	{
		binder->bind (statement, instances, error_message_m);
	}
	else
	{
		error_message_m << L"Target of statement is not bindable\n";		
	}
}

void lambda_p::binder::routine_binder::reset ()
{
	error_message_m.clear ();
}

void lambda_p::binder::routine_binder::populate_unbound (::boost::shared_ptr < ::lambda_p::core::routine> routine_a, ::lambda_p::core::statement * statement, ::boost::shared_ptr < ::lambda_p::binder::node_binder> & binder)
{
	assert (statement->target != NULL);
	::lambda_p::core::node * target (statement->target->declaration);
	::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> >::iterator search (instances.find (target));
	if (search != instances.end ())
	{
		instances [target] = search->second;
		::boost::shared_ptr < ::lambda_p::binder::node_instance> binder_l (search->second);
		binder = ::boost::dynamic_pointer_cast < ::lambda_p::binder::node_binder> (binder_l);
	}
	else
	{
		unbound_statements [target] = statement;
	}
	for (::std::vector < ::lambda_p::core::node *>::iterator i = statement->parameters.begin (); binder.get () != NULL && i != statement->parameters.end (); ++i)
	{
		::lambda_p::core::node * node (*i);
		::lambda_p::core::node_id node_id (node->node_type ());
		switch (node_id)
		{
		case ::lambda_p::core::node_reference:
			{
				::lambda_p::core::reference * reference (static_cast < ::lambda_p::core::reference *> (node));
				::lambda_p::core::node * target (reference->declaration);
				::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> >::iterator search (instances.find (target));
				if (search != instances.end ())
				{
					instances [node] = search->second;
				}
				else
				{
					binder.reset ();
					unbound_statements [target] = statement;
				}
			}
			break;
		default:
			// Data and declarations don't need to be resolved
			break;
		}
	}
}

bool lambda_p::binder::routine_binder::error ()
{
	bool result (!error_message_m.str ().empty ());
	return result;
}

void lambda_p::binder::routine_binder::error_message (::std::wstring & target)
{
	target.append (error_message_m.str ());
}