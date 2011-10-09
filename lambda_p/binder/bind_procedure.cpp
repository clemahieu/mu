#include "bind_procedure.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/binder/node_binder.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unresolved_statement.h>
#include <lambda_p/errors/binder_string_error.h>
#include <lambda_p/errors/target_not_bindable.h>

#include <sstream>

lambda_p::binder::bind_procedure::bind_procedure (::boost::shared_ptr < ::lambda_p::core::routine> routine_a)
	: routine (routine_a)
{
}

lambda_p::binder::bind_procedure::~bind_procedure(void)
{
}

void lambda_p::binder::bind_procedure::operator () (::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	::std::vector < ::lambda_p::core::statement *>::iterator i = routine->statements.begin ();
	size_t statement_count (routine->statements.size ());
	for (size_t i = 0; i < statement_count; ++i)
	{	
		bind_statement (i, problems);
	}
	for (::std::map < size_t, size_t>::iterator i = unbound_statements.begin (); i != unbound_statements.end (); ++i)
	{
		problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::unresolved_statement (i->second)));
	}
}

void lambda_p::binder::bind_procedure::bind_statement (size_t statement, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{	
	::boost::shared_ptr < ::lambda_p::binder::node_binder> binder;
	populate_unbound (statement, binder, problems);
	if (binder.get () != NULL)
	{
		size_t previous_size (problems.size ());
		binder->bind (routine->statements [statement], routine->instances, problems);
		if (problems.size () != previous_size)
		{
			::std::wstring message (L"Bind error for statement: ");
			::std::wstringstream stream;
			stream << statement;
			message.append (stream.str ());
			problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::binder_string_error (::std::wstring (L"bind_procedure"), message)));

		}
		retry_bind (statement, problems); // We might have resolved what was needed for a previously unresolved bind
	}
	else
	{
		// Could be resolved out of order, wait until end
	}
}

void error_message (::std::wostream & stream)
{
}

void lambda_p::binder::bind_procedure::populate_unbound (size_t statement, ::boost::shared_ptr < ::lambda_p::binder::node_binder> & binder, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	::lambda_p::core::statement * statement_l (routine->statements [statement]);
	assert (statement_l->target < routine->nodes);
	::boost::shared_ptr < ::lambda_p::binder::node_instance> binder_l;
	copy_declaration_binder (binder_l, statement_l->target);
	if (binder_l.get () != NULL)
	{
		binder = ::boost::dynamic_pointer_cast < ::lambda_p::binder::node_binder> (binder_l);
		if (binder.get () != NULL)
		{
			for (::std::vector < size_t>::iterator i = statement_l->association->parameters.begin (); binder.get () != NULL && i != statement_l->association->parameters.end (); ++i)
			{
				size_t node (*i);
				copy_declaration_binder (binder_l, node);
				if (binder_l.get () == NULL)
				{
					binder.reset (); // Target and all arguments must be bound, if we can't find the binder for an argument, we can't bind the statement
					unbound_statements [node] = statement;
				}
			}
		}
		else
		{
			problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::target_not_bindable));
		}
	}
	else
	{
		unbound_statements [statement_l->target] = statement;
	}
}

void lambda_p::binder::bind_procedure::copy_declaration_binder (::boost::shared_ptr < ::lambda_p::binder::node_instance> & binder, size_t node)
{
	size_t declaration (node);
	if (declaration < routine->instances.instances.size ())
	{
		binder = routine->instances [declaration];
	}
	else
	{
		binder.reset ();
	}
}

void lambda_p::binder::bind_procedure::retry_bind (size_t statement, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	::lambda_p::core::statement * statement_l (routine->statements [statement]);
	for (::std::vector < size_t>::iterator i = statement_l->association->results.begin (); i != statement_l->association->results.end (); ++i)
	{
		::std::map < size_t, size_t>::iterator search (unbound_statements.find (*i));
		if (search != unbound_statements.end ())
		{
			size_t retry_statement (search->second);
			unbound_statements.erase (search);
			bind_statement (retry_statement, problems);
		}
	}
}