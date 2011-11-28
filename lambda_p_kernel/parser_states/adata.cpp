#include "adata.h"

#include <lambda_p/tokens/identifier.h>
#include <lambda_p/parser/error.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/parser/association_target.h>
#include <lambda_p/parser/routine.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_kernel/nodes/adata.h>

#include <sstream>

lambda_p_kernel::parser_states::adata::adata (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::parser::association_target & target_a)
	: parser (parser_a),
	routine (routine_a),
	target (target_a)
{
}

void lambda_p_kernel::parser_states::adata::parse (lambda_p::tokens::token * token)
{
	lambda_p::tokens::identifier * identifier (dynamic_cast <lambda_p::tokens::identifier *> (token));
	if (identifier != nullptr)
	{
		std::string adata;
		bool valid (true);
		for (auto i (identifier->string.begin ()); i != identifier->string.end (); ++i)
		{
			wchar_t val (*i);
			if (val <= CHAR_MAX)
			{
				adata.push_back ((char)val);
			}
			else
			{
				std::wstringstream message;
				message << L"Unable to use as ASCII character: ";
				message << val;
				boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message.str ()));
				parser.state.push (new_state);
				valid = false;
				i = identifier->string.end ();
			}
		}
		if (valid)
		{			
			auto location (target.sink_argument ());
			size_t declaration (routine.routine_m->inject_declaration (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::adata (adata))));
			location (declaration);
			parser.state.pop ();
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Expecting identifier while parsing adata, have: ";
		message << parser.token_type_name (token);
		boost::shared_ptr <lambda_p::parser::state> new_state (new lambda_p::parser::error (message.str ()));
		parser.state.push (new_state);
	}
}