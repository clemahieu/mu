#include "routine_binder.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/binder/node_binder.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unresolved_statement.h>
#include <lambda_p/errors/binder_string_error.h>

#include <sstream>

lambda_p::binder::routine_binder::routine_binder (::boost::shared_ptr < ::lambda_p::core::routine> routine_a)
	: routine (routine_a),
	instances (routine_a->instances)
{
}

lambda_p::binder::routine_binder::~routine_binder(void)
{
}

void lambda_p::binder::routine_binder::operator () ()
{
	::std::vector < ::lambda_p::core::statement *>::iterator i = routine->statements.begin ();
	size_t statement_count (routine->statements.size ());
	for (size_t i = 0; i < statement_count; ++i)
	{	
		bind_statement (i);
	}
	for (::std::map < size_t, size_t>::iterator i = unbound_statements.begin (); i != unbound_statements.end (); ++i)
	{
		errors.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::unresolved_statement (i->second)));
	}
}

void lambda_p::binder::routine_binder::bind_statement (size_t statement)
{	
	::boost::shared_ptr < ::lambda_p::binder::node_binder> binder;
	populate_unbound (statement, binder);
	if (binder.get () != NULL)
	{
		size_t previous_size (errors.size ());
		binder->bind (routine->statements [statement], instances, errors);
		if (errors.size () != previous_size)
		{
			::std::wstring message (L"Bind error for statement: ");
			::std::wstringstream stream;
			stream << statement;
			message.append (stream.str ());
			errors.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::binder_string_error (::std::wstring (L"routine_binder"), message)));

		}
		retry_bind (statement); // We might have resolved what was needed for a previously unresolved bind
	}
	else
	{
		// Could be resolved out of order, wait until end
	}
}

void error_message (::std::wostream & stream)
{
}

void lambda_p::binder::routine_binder::reset ()
{
	errors.clear ();
}

void lambda_p::binder::routine_binder::populate_unbound (size_t statement, ::boost::shared_ptr < ::lambda_p::binder::node_binder> & binder)
{
	::lambda_p::core::statement * statement_l (routine->statements [statement]);
	assert (statement_l->target < routine->nodes);
	::boost::shared_ptr < ::lambda_p::binder::node_instance> binder_l;
	copy_declaration_binder (binder_l, statement_l->target);
	if (binder_l.get () != NULL)
	{
		binder = ::boost::dynamic_pointer_cast < ::lambda_p::binder::node_binder> (binder_l);
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
		unbound_statements [statement_l->target] = statement;
	}
}

void lambda_p::binder::routine_binder::copy_declaration_binder (::boost::shared_ptr < ::lambda_p::binder::node_instance> & binder, size_t node)
{
	size_t declaration (node);
	::std::map < size_t, ::boost::shared_ptr < ::lambda_p::binder::node_instance> >::iterator search (instances.find (declaration));
	if (search != instances.end ())
	{
		binder = search->second;
	}
	else 
	{
		binder.reset ();
	}
}

void lambda_p::binder::routine_binder::retry_bind (size_t statement)
{
	::lambda_p::core::statement * statement_l (routine->statements [statement]);
	for (::std::vector < size_t>::iterator i = statement_l->association->results.begin (); i != statement_l->association->results.end (); ++i)
	{
		::std::map < size_t, size_t>::iterator search (unbound_statements.find (*i));
		if (search != unbound_statements.end ())
		{
			size_t retry_statement (search->second);
			unbound_statements.erase (search);
			bind_statement (retry_statement);
		}
	}
}

bool lambda_p::binder::routine_binder::error ()
{
	bool result (!errors.empty ());
	return result;
}