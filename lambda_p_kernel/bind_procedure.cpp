#include "bind_procedure.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/binder/binder.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unresolved_statement.h>
#include <lambda_p/errors/binder_string_error.h>
#include <lambda_p/errors/target_not_bindable.h>

#include <sstream>

lambda_p_kernel::bind_procedure::bind_procedure (boost::shared_ptr < lambda_p::core::routine> routine_a, lambda_p::binder::node_list & nodes_a)
	: routine (routine_a),
	nodes (nodes_a)
{
}

lambda_p_kernel::bind_procedure::~bind_procedure(void)
{
}

void lambda_p_kernel::bind_procedure::operator () (lambda_p::errors::error_list & problems)
{
	nodes.merge (routine->injected, problems);
	if (problems.errors.empty ())
	{
		size_t statement_count (routine->statements.size ());
		for (size_t i = 0; i < statement_count; ++i)
		{	
			bind_statement (i, problems);
		}
		for (auto i = unbound_statements.begin (); i != unbound_statements.end (); ++i)
		{
			problems (new lambda_p::errors::unresolved_statement (i->second));
		}
	}
}

void lambda_p_kernel::bind_procedure::bind_statement (size_t statement, lambda_p::errors::error_list & problems)
{	
	boost::shared_ptr < lambda_p::binder::binder> binder;
	populate_unbound (statement, binder, problems);
	if (binder.get () != NULL)
	{
		size_t previous_size (problems.errors.size ());
		binder->bind (routine->statements [statement], nodes, problems);
		if (problems.errors.size () != previous_size)
		{
			std::wstring message (L"Bind error for statement: ");
			std::wstringstream stream;
			stream << statement;
			message.append (stream.str ());
			problems (new lambda_p::errors::binder_string_error (std::wstring (L"bind_procedure"), message));

		}
		retry_bind (statement, problems); // We might have resolved what was needed for a previously unresolved bind
	}
	else
	{
		// Could be resolved out of order, wait until end
	}
}

void error_message (std::wostream & stream)
{
}

void lambda_p_kernel::bind_procedure::populate_unbound (size_t statement, boost::shared_ptr <lambda_p::binder::binder> & binder, lambda_p::errors::error_list & problems)
{
	lambda_p::core::statement * statement_l (routine->statements [statement]);
	assert (statement_l->target < routine->nodes);
	boost::shared_ptr <lambda_p::binder::node> binder_l;
	copy_declaration_binder (binder_l, statement_l->target);
	if (binder_l.get () != NULL)
	{
		binder = boost::dynamic_pointer_cast < lambda_p::binder::binder> (binder_l);
		if (binder.get () != NULL)
		{
			for (auto i = statement_l->association->parameters.begin (); binder.get () != NULL && i != statement_l->association->parameters.end (); ++i)
			{
				size_t node (*i);
				copy_declaration_binder (binder_l, node);
				if (binder_l.get () == NULL)
				{
					binder.reset (); // Target and all arguments must be bound, if we can't find the binder for an argument, we can't bind the statement
					unbound_statements [node] = statement; // Record this unbound statement and the needed node to be retried in case an argument is later bound or for issuing a problem once all statements have been attempted
				}
			}
		}
		else
		{
			problems (new lambda_p::errors::target_not_bindable);
		}
	}
	else
	{
		unbound_statements [statement_l->target] = statement;
	}
}

void lambda_p_kernel::bind_procedure::copy_declaration_binder (boost::shared_ptr <lambda_p::binder::node> & binder, size_t node)
{
	size_t declaration (node);
	if (declaration < nodes.nodes.size ())
	{
		binder = nodes [declaration];
	}
	else
	{
		binder.reset ();
	}
}

void lambda_p_kernel::bind_procedure::retry_bind (size_t statement, lambda_p::errors::error_list & problems)
{
	lambda_p::core::statement * statement_l (routine->statements [statement]);
	for (auto i = statement_l->association->results.begin (); i != statement_l->association->results.end (); ++i)
	{
		auto search (unbound_statements.find (*i));
		if (search != unbound_statements.end ())
		{
			size_t retry_statement (search->second);
			unbound_statements.erase (search);
			bind_statement (retry_statement, problems);
		}
	}
}