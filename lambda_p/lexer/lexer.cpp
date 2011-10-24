#include <lambda_p/lexer/lexer.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/tokens/identifier.h>
#include <lambda_p/tokens/routine_end.h>
#include <lambda_p/tokens/divider.h>
#include <lambda_p/tokens/data.h>
#include <lambda_p/tokens/complex_identifier.h>

#include <lambda_p/lexer/state.h>
#include <lambda_p/lexer/begin.h>
#include <lambda_p/lexer/error.h>
#include <lambda_p/lexer/control.h>
#include <lambda_p/lexer/identifier.h>
#include <lambda_p/lexer/multiline_comment.h>
#include <lambda_p/lexer/singleline_comment.h>
#include <lambda_p/lexer/complex_identifier.h>

#include <boost/circular_buffer.hpp>

lambda_p::lexer::lexer::lexer (boost::function < void (lambda_p::tokens::token *)> target_a)
	: target (target_a)
{
	state.push (new lambda_p::lexer::begin);
}

lambda_p::lexer::lexer::~lexer ()
{
}

void lambda_p::lexer::lexer::operator () (wchar_t character)
{
	lex_internal (character);
}

void lambda_p::lexer::lexer::reset ()
{
	while (!state.empty ())
	{
		pop_state ();
	}
	state.push (new lambda_p::lexer::begin);
}

bool lambda_p::lexer::lexer::error ()
{
	bool result;
	if (state.empty ())
	{
		result = false;
	}
	else
	{
		result = state.top ()->state_type () == lambda_p::lexer::state_error;
	}
	return result;
}
	
void lambda_p::lexer::lexer::error_message (std::wstring & target)
{
	lambda_p::lexer::error * error_l = (static_cast < lambda_p::lexer::error *> (state.top ()));
	target = error_l->message;
}

void lambda_p::lexer::lexer::lex_internal (wchar_t character)
{
	state_id state_l (state.top ()->state_type ());
	switch (state_l)
	{
	case lambda_p::lexer::state_error:
		lex_error (character);
		break;
	case lambda_p::lexer::state_begin:
		lex_begin (character);
		break;
	case lambda_p::lexer::state_control:
		lex_control (character);
		break;
	case lambda_p::lexer::state_identifier:
		lex_identifier (character);
		break;
	case lambda_p::lexer::state_multiline_comment:
		lex_multiline_comment (character);
		break;
	case lambda_p::lexer::state_singleline_comment:
		lex_singleline_comment (character);
		break;
	case lambda_p::lexer::state_complex_identifier:
		lex_complex_identifier (character);
		break;
	default:
		assert (false);
	}
}

void lambda_p::lexer::lexer::lex_error (wchar_t character)
{
	// Do nothing, remain in error state
}

void lambda_p::lexer::lexer::lex_begin (wchar_t character)
{
	switch (character)
	{
	case L' ':
	case L'\t':
	case L'\n':
	case L'\f':
	case L'\0':
		// Eat whitespace
		break;
	case L'`':
		{
			lambda_p::tokens::data * token = new lambda_p::tokens::data;
			target (token);
		}
		break;
	case L'|':
		state.push (new lambda_p::lexer::complex_identifier);
		break;
	case L';':
		{
			lambda_p::tokens::divider * token = new lambda_p::tokens::divider;
			target (token);
		}
		break;
	case L':':
		state.push (new lambda_p::lexer::control);
		break;
	case L'\uffff':
		pop_state ();
		break;
	default:
		state.push (new lambda_p::lexer::identifier);
		lex_internal (character);
		break;
	}
}

void lambda_p::lexer::lexer::lex_control (wchar_t character)
{
	lambda_p::lexer::control * state_l (static_cast < lambda_p::lexer::control *> (state.top ()));
	if (character != '\uffff')
	{
		switch (character)
		{
		case L'*':
			pop_state ();
			state.push (new lambda_p::lexer::multiline_comment);
			break;
		case L'/':
			pop_state ();
			state.push (new lambda_p::lexer::singleline_comment);
			break;
		case L';':
			{
				lambda_p::tokens::routine_end * token = new lambda_p::tokens::routine_end;
				target (token);
				pop_state ();
			}
			break;
		default:
			std::wstring message (L"Unknown token: #");
			message.push_back (character);
			state.push (new lambda_p::lexer::error (message));
			break;
		}
	}
	else
	{
		std::wstring message (L"End of stream when parsing control character");
		message.push_back (character);
		state.push (new lambda_p::lexer::error (message));
	}
}

void lambda_p::lexer::lexer::lex_multiline_comment (wchar_t character)
{
	lambda_p::lexer::multiline_comment * state_l (static_cast < lambda_p::lexer::multiline_comment *> (state.top ()));
	if (character != L'\uffff')
	{
		if (state_l->have_colon)
		{
			switch (character)
			{
			case L'*':
				pop_state ();
				break;
			case L':':
				// Remain in have_colon state
				break;
			default:
				state_l->have_colon = false;
				break;
			}
		}
		else
		{
			switch (character)
			{
			case L':':
				state_l->have_colon = true;
				break;
			}
		}
	}
	else
	{
		std::wstring message (L"End of stream inside multiline comment");
		state.push (new lambda_p::lexer::error (message));
	}
}

void lambda_p::lexer::lexer::lex_singleline_comment (wchar_t character)
{
	lambda_p::lexer::singleline_comment * state_l (static_cast < lambda_p::lexer::singleline_comment *> (state.top ()));
	switch (character)
	{
	case L'\n':
	case L'\f':
		pop_state ();
		break;
	case L'\uffff':
		pop_state ();
		lex_internal (character);
		break;
	default:
		// Eat comment
		break;
	}
}

void lambda_p::lexer::lexer::lex_complex_identifier (wchar_t character)
{
	lambda_p::lexer::complex_identifier * state_l (static_cast < lambda_p::lexer::complex_identifier *> (state.top ()));
	if (character != L'\uffff')
	{
		if (!state_l->have_end_token)
		{
			switch (character)
			{
			case L'|':
				state_l->have_end_token = true;
				state_l->last_characters.resize (state_l->end_token.size ());
				break;
			default:
				state_l->end_token.push_back (character);
				break;
			}
		}
		else
		{		
			state_l->last_characters.push_back (character);
			state_l->data.push_back (character);
		}
		if (state_l->have_end_token && state_l->match ())
		{
			state_l->data.resize (state_l->data.size () - state_l->end_token.size ());
			lambda_p::tokens::complex_identifier * token (new lambda_p::tokens::complex_identifier (state_l->data, state_l->end_token));
			target (token);
			pop_state ();
		}
	}
	else
	{
		std::wstring message (L"End of file while parsing complex identifier");
		lambda_p::lexer::error * error (new lambda_p::lexer::error (message));
		state.push (error);
	}
}

void lambda_p::lexer::lexer::lex_identifier (wchar_t character)
{				
	lambda_p::lexer::identifier * state_l (static_cast < lambda_p::lexer::identifier *> (state.top ()));
	switch (character)
	{
	case L' ':
	case L'\t':
	case L'\n':
	case L'\f':
	case L';':
	case L'`':
	case L'|':
	case L':':
	case L'\0':
	case L'\uffff':
		{
			lambda_p::tokens::identifier * identifier = new lambda_p::tokens::identifier (state_l->string);
			target (identifier);
			pop_state ();
			lex_internal (character);
		}
		break;
	default:
		state_l->string.push_back (character);
		break;
	}
}

void lambda_p::lexer::lexer::pop_state ()
{
	delete state.top ();
	state.pop ();
}