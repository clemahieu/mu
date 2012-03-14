#include "hex_code.h"

#include <mu/core/errors/error_target.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/lexer/error.h>
#include <mu/io/lexer/identifier.h>

mu::io::lexer::hex_code::hex_code (size_t digits_a, mu::io::lexer::identifier & identifier_a)
	: identifier (identifier_a),
	index (0),
	digits (digits_a),
	result (0)
{
	assert (digits <= 8);
}

void mu::io::lexer::hex_code::lex (wchar_t character)
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
			(*identifier.lexer.errors) (message);
			identifier.lexer.state.push (boost::shared_ptr <mu::io::lexer::error> (new mu::io::lexer::error));
			break;
	}
}