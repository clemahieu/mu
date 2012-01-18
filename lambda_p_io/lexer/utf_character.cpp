#include "utf_character.h"

#include <lambda_p_io/lexer/lexer.h>

lambda_p_io::lexer::utf_character::utf_character (lambda_p_io::lexer::lexer & lexer_a)
	: lexer (lexer_a),
	nibble (0),
	last_nibble (~0)
{
}

void lambda_p_io::lexer::utf_character::lex (wchar_t character)
{
	assert (nibble < 12);
	switch (character)
	{		
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
		case L'a':
		case L'A':
		case L'b':
		case L'B':
		case L'c':
		case L'C':
		case L'd':
		case L'D':
		case L'e':
		case L'E':
		case L'f':
		case L'F':
			process (character);
			break;
		case L' ':
		case L'\t':
		case L'\n':
		case L'\f':
		case L'\0':
		case L':':
		case L';':
		case L'|':
		case L'[':
		case L']':
		default:
			break;
	}
}

void lambda_p_io::lexer::utf_character::process (wchar_t character)
{
	add_nibble (character);
	++nibble;
	set_size ();
	terminate ();
}

void lambda_p_io::lexer::utf_character::set_size ()
{
	if (nibble == 2)
	{
		assert (last_nibble == ~0);
		unsigned char byte (bytes [0]);
		size_t first_zero (0);
		for (auto byte_l (byte); byte_l & 0x80 != 0; byte_l << 1)
		{
			++first_zero;
		}
		first_zero = first_zero == 0 ? 1 : first_zero;
		last_nibble = first_zero << 1;
	}
}

void lambda_p_io::lexer::utf_character::terminate ()
{
	if (last_nibble == nibble)
	{

	}
}

void lambda_p_io::lexer::utf_character::add_nibble (wchar_t character)
{
	unsigned char character_l (character);
	switch (character)
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
	switch (character)
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
	character_l = (nibble & 0x1) != 0 ? character_l << 4 : character_l;
	auto position (nibble >> 1);
	auto existing (bytes [position]);
	bytes [position] = existing | character_l;
}