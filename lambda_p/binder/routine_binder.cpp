#include "routine_binder.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/binder/node_binder.h>
#include <lambda_p/binder/bound_routine.h>

lambda_p::binder::routine_binder::routine_binder(::std::map < ::lambda_p::core::node *, ::lambda_p::binder::node_instance *> instances_a)
	: instances (instances_a),
	routine (new ::lambda_p::binder::bound_routine)
{
}

lambda_p::binder::routine_binder::~routine_binder(void)
{
}

void lambda_p::binder::routine_binder::operator () (::lambda_p::core::routine * routine_a)
{
	for (::std::vector < ::lambda_p::core::statement *>::iterator i = routine_a->statements.begin (); i != routine_a->statements.end (); ++i)
	{
		bool resolved;
		::lambda_p::core::statement * statement (*i);
		populate_unresolved (statement, resolved);
		if (resolved)
		{
			::std::vector < ::lambda_p::core::node *>::iterator i = statement->arguments.begin ();
			::lambda_p::core::node * node (*i);
			::std::map < ::lambda_p::core::node *, ::lambda_p::binder::node_instance *>::iterator search (instances.find (node));
			::lambda_p::binder::node_binder * binder (dynamic_cast < ::lambda_p::binder::node_binder *> (search->second));
			if (binder != NULL)
			{
				::std::wstring problems;
				binder->bind (statement, instances, *routine.get (), problems);
				error_message_m.append (problems);
			}
			else
			{
				error_message_m.append (L"Target of statement is not bindable\n");
			}
		}
		else
		{
			// Unbound nodes were put in to unbound_statements by populate_unresolved
		}
	}
	for (::std::map < ::lambda_p::core::node *, ::lambda_p::core::statement *>::iterator i = unbound_statements.begin (); i != unbound_statements.end (); ++i)
	{
		error_message_m.append (L"Unresolved node\n");
	}
}

void lambda_p::binder::routine_binder::reset ()
{
	error_message_m.clear ();
}

void lambda_p::binder::routine_binder::populate_unresolved (::lambda_p::core::statement * statement, bool & resolved)
{
	resolved = true;
	for (::std::vector < ::lambda_p::core::node *>::iterator i = statement->arguments.begin (); i != statement->arguments.end (); ++i)
	{
		::lambda_p::core::node * node (*i);
		::lambda_p::core::node_id node_id (node->node_type ());
		switch (node_id)
		{
		case ::lambda_p::core::node_data:
			break;
		case ::lambda_p::core::node_parameter_ref:
			break;
		case ::lambda_p::core::node_result:
			break;
		case ::lambda_p::core::node_result_ref:
			::std::map < ::lambda_p::core::node *, ::lambda_p::binder::node_instance *>::iterator search (instances.find (node));
			bool node_resolved (search != instances.end ());
			if (!node_resolved)
			{
				unbound_statements [node] = statement;
				resolved = false;
			}
			break;
		}
	}
}