#include <mu/core/context.h>

#include <sstream>

mu::core::context::context ()
{
}

mu::core::context::context (mu::core::position first_a, mu::core::position last_a)
	: first (first_a),
	last (last_a)
{
}

mu::core::context::context (size_t first_row, size_t first_column, size_t first_character, size_t last_row, size_t last_column, size_t last_character)
	: first (first_row, first_column, first_character),
	last (last_row, last_column, last_character)
{
}

bool mu::core::context::operator == (mu::core::context const & other)
{
	bool result (first == other.first && last == other.last);
	return result;
}

std::wstring mu::core::context::string ()
{
	std::wstringstream result;
	result << first.row;
	result << L',';
	result << first.column;
	result << L',';
	result << first.character;
	result << L':';
	result << last.row;
	result << L',';
	result << last.column;
	result << L',';
	result << last.character;
	return result.str ();
}