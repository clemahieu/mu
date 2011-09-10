#include "statement.h"

#include <lambda_p/parser/body.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/simple_parser.h>

lambda_p::parser::statement::statement(::boost::shared_ptr < ::lambda_p::parser::body> body_a, ::std::wstring statement_name_a)
	: statement_name (statement_name_a),
	body (body_a),
	have_target (false),
	have_argument (false),
	statement_m (body_a->routine ()->add_statement ())
{
}

lambda_p::parser::statement::~statement(void)
{
}

::lambda_p::parser::state_id lambda_p::parser::statement::state_type ()
{
	return lambda_p::parser::state_statement;
}

::boost::shared_ptr < ::lambda_p::core::routine> & lambda_p::parser::statement::routine ()
{
	return body->routine ();
}

void lambda_p::parser::statement::sink_reference (::lambda_p::parser::simple_parser & parser, ::lambda_p::parser::reference_identifiers reference)
{
	size_t current_statement (statement_m->routine->statements.size () - 1);
	size_t current_argument (statement_m->routine->statements [current_statement]->arguments.size ());
	if (reference.statement.compare (body->routine_name) == 0)
	{
		::std::map < ::std::wstring, size_t>::iterator search = body->parameter_positions.find (reference.argument);
		if (search != body->parameter_positions.end ())
		{
			::lambda_p::core::parameter_ref * ref = routine ()->add_parameter_ref (search->second, current_statement, current_argument);
			statement_m->add_argument (ref);
		}
		else
		{
			::std::wstring message (L"Trying to parse a parameter_ref, identifier is not a parameter");
			::boost::shared_ptr < ::lambda_p::parser::state> new_state (new ::lambda_p::parser::error (message));
			parser.state.push (new_state);
		}
	}
	else
	{
		::std::map < ::lambda_p::parser::reference_identifiers, ::lambda_p::parser::reference_position>::iterator search = body->positions.find (reference);
		if (search != body->positions.end ())
		{
			::lambda_p::core::reference * ref = routine ()->add_result_ref (search->second.statement, search->second.argument, current_statement, current_argument);
			statement_m->add_argument (ref);
		}
		else
		{
			::lambda_p::core::reference * ref = routine ()->add_result_ref (-1, -1, current_statement, current_argument);
			statement_m->add_argument (ref);
			body->unresolved_references.insert (::std::multimap < ::lambda_p::parser::reference_identifiers, ::lambda_p::core::reference *>::value_type (reference, ref));
		}
	}
}

void lambda_p::parser::statement::sink_data (::lambda_p::parser::simple_parser & parser, ::lambda_p::tokens::identifier * identifier)
{
	size_t current_statement (statement_m->routine->statements.size () - 1);
	size_t current_argument (statement_m->routine->statements [current_statement]->arguments.size ());
	size_t size (identifier->string.size () * sizeof (wchar_t));
	::boost::shared_array <uint8_t> data (new uint8_t [size]);
	memcpy (data.get (), identifier->string.c_str (), size);
	statement_m->add_argument (routine ()->add_data (data, size, current_statement, current_argument));
}

void lambda_p::parser::statement::sink_declaration (::lambda_p::parser::simple_parser & parser, ::lambda_p::tokens::identifier * identifier)
{
	size_t current_statement (statement_m->routine->statements.size () - 1);
	size_t current_argument (statement_m->routine->statements [current_statement]->arguments.size ());
	::lambda_p::parser::reference_identifiers reference (statement_name, identifier->string);
	::lambda_p::parser::reference_position position (current_statement, current_argument);
	body->positions [reference] = position;
	statement_m->add_argument (routine ()->add_result (current_statement, current_argument));
}