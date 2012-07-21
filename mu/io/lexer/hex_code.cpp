#include "hex_code.h"

#include <mu/core/errors/error_target.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/lexer/error.h>
#include <mu/io/lexer/identifier.h>
#include <mu/io/lexer/context.h>

#include <gc_cpp.h>

mu::io::lexer::hex_code::hex_code (size_t digits_a, mu::io::lexer::identifier & identifier_a)
	: identifier (identifier_a),
	index (0),
	digits (digits_a),
	result (0)
{
	assert (digits <= 8);
}

void mu::io::lexer::hex_code::lex (mu::io::lexer::context const & context_a)
{
	++index;
	switch (context_a.character)
	{		
		case U'a':
		case U'b':
		case U'c':
		case U'd':
		case U'e':
		case U'f':
		case U'A':
		case U'B':
		case U'C':
		case U'D':
		case U'E':
		case U'F':
		case U'0':
		case U'1':
		case U'2':
		case U'3':
		case U'4':
		case U'5':
		case U'6':
		case U'7':
		case U'8':
		case U'9':
		{
			unsigned long character_l (context_a.character);
			switch (character_l)
			{
				case U'a':
				case U'b':
				case U'c':
				case U'd':
				case U'e':
				case U'f':
					character_l -= 0x20;
					break;
			}
			switch (character_l)
			{
				case U'A':
				case U'B':
				case U'C':
				case U'D':
				case U'E':
				case U'F':
					character_l -= 0x7;
					break;
			}
			character_l -= 0x30;
			unsigned long bits (character_l << ((digits - index) << 2));
			result = result | bits;
			if (index == digits)
			{
                mu::io::lexer::context context;
                context.position = context_a.position;
                context.character = result;
				identifier.add (context);
				identifier.lexer.state.pop ();
			}
		}
		break;
		default:
			mu::string message (U"Invalid hex digit: ");
			message.push_back (context_a.character);
			(*identifier.lexer.errors) (message);
			identifier.lexer.state.push (new (GC) mu::io::lexer::error);
			break;
	}
}