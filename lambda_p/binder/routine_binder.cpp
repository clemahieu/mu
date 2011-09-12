#include "routine_binder.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/binder/node_binder.h>
#include <lambda_p/binder/bound_routine.h>

#include <sstream>

lambda_p::binder::routine_binder::routine_binder ()
	: routine (new ::lambda_p::binder::bound_routine)
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
		error_message_m.append (L"Unresolved node\n");
	}
}

void lambda_p::binder::routine_binder::bind_statement (::boost::shared_ptr < ::lambda_p::core::routine> routine_a, ::lambda_p::core::statement * statement)
{	
	::boost::shared_ptr < ::lambda_p::binder::node_binder> binder;
	populate_unbound (routine_a, statement, binder);
	if (binder.get () != NULL)
	{
		::std::wstring problems;
		binder->bind (statement, instances, *routine.get (), ::std::wstringstream (problems));
		error_message_m.append (problems);
	}
	else
	{
		error_message_m.append (L"Target of statement is not bindable\n");		
	}
}

void lambda_p::binder::routine_binder::reset ()
{
	error_message_m.clear ();
}

void lambda_p::binder::routine_binder::populate_unbound (::boost::shared_ptr < ::lambda_p::core::routine> routine_a, ::lambda_p::core::statement * statement, ::boost::shared_ptr < ::lambda_p::binder::node_binder> & binder)
{
	::std::vector < ::lambda_p::core::node *>::iterator i = statement->arguments.begin ();
	assert (i != statement->arguments.end ()); // Statement must have target argument	
	::lambda_p::core::node * node (*i);
	::lambda_p::core::node_id node_id (node->node_type ());
	switch (node_id)
	{
	case ::lambda_p::core::node_reference:
		{
			::lambda_p::core::reference * reference (static_cast < ::lambda_p::core::reference *> (node));
			::lambda_p::core::node * target (routine_a->statements [reference->target_statement]->arguments [reference->target_argument]);
			::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> >::iterator search (instances.find (target));
			if (search != instances.end ())
			{
				::boost::shared_ptr < ::lambda_p::binder::node_instance> binder_l (search->second);
				binder = ::boost::dynamic_pointer_cast < ::lambda_p::binder::node_binder> (binder_l);
			}
			else
			{
				unbound_statements [target] = statement;
			}
		}
		break;
	default:
		assert (false); // Target is not a reference
		break;
	}
	++i;
	while (binder.get () != NULL && i != statement->arguments.end ())
	{
		::lambda_p::core::node * node (*i);
		::lambda_p::core::node_id node_id (node->node_type ());
		switch (node_id)
		{
		case ::lambda_p::core::node_reference:
			{
				::lambda_p::core::reference * reference (static_cast < ::lambda_p::core::reference *> (node));
				::lambda_p::core::node * target (routine_a->statements [reference->target_statement]->arguments [reference->target_argument]);
				::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> >::iterator search (instances.find (target));
				if (search == instances.end ())
				{
					binder.reset ();
					unbound_statements [target] = statement;
				}
			}
			break;
		default:
			assert (false); // Target is not a reference
			break;
		}
		++i;
	}
}

bool lambda_p::binder::routine_binder::error ()
{
	bool result (!error_message_m.empty ());
	return result;
}

void lambda_p::binder::routine_binder::error_message (::std::wstring & target)
{
	target.append (error_message_m);
}