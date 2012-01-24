#include "hex_code.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/lexer/error.h>
#include <lambda_p_io/lexer/identifier.h>

lambda_p_io::lexer::hex_code::hex_code (size_t digits_a, lambda_p_io::lexer::identifier & identifier_a)
	: identifier (identifier_a),
	result (0),
	index (0),
	digits (digits_a)
{
	assert (digits <= 8);
}

void lambda_p_io::lexer::hex_code::lex (wchar_t character)
{
	++index;
	switch (character)
	{		
		case L'a':
		case L'b':
		case L'c':
		case L'd':
		case L'e':
		case L'f':
		case L'A':
		case L'B':
		case L'C':
		case L'D':
		case L'E':
		case L'F':
		case L'0':
		case L'1':
		case L'2':
		case L'3':
		case L'4':
		case L'5':
		case L'6':
		case L'7':
		case L'8':
		case L'9':
		{
			unsigned long character_l (character);
			switch (character_l)
			{
				case L'a':
				case L'b':
				case L'c':
				case L'd':
				case L'e':
				case L'f':
					character_l -= 0x20;
					break;
			}
			switch (character_l)
			{
				case L'A':
				case L'B':
				case L'C':
				case L'D':
				case L'E':
				case L'F':
					character_l -= 0x7;
					break;
			}
			character_l -= 0x30;
			unsigned long bits (character_l << ((digits - index) << 2));
			result = result | bits;
			if (index == digits)
			{
				identifier.add (result);
				identifier.lexer.state.pop ();
			}
		}
		break;
		default:
			std::wstring message (L"Invalid hex digit: ");
			message.push_back (character);
			(*identifier.lexer.errors) (message, lambda_p::context (identifier.lexer.position, identifier.lexer.position));
			identifier.lexer.state.push (boost::shared_ptr <lambda_p_io::lexer::error> (new lambda_p_io::lexer::error));
			break;
	}
}