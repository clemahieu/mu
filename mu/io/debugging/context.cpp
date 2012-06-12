#include <mu/io/debugging/context.h>

#include <sstream>

#include <boost/make_shared.hpp>

mu::io::debugging::context::context ()
{
}

mu::io::debugging::context::context (mu::io::debugging::position first_a, mu::io::debugging::position last_a)
	: first (first_a),
	last (last_a)
{
}

mu::io::debugging::context::context (size_t first_row, size_t first_column, size_t first_character, size_t last_row, size_t last_column, size_t last_character)
	: first (first_row, first_column, first_character),
	last (last_row, last_column, last_character)
{
}

bool mu::io::debugging::context::operator == (mu::io::debugging::context const & other)
{
	bool result (first == other.first && last == other.last);
	return result;
}

std::wstring mu::io::debugging::context::string ()
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