#include "context.h"

#include <sstream>

lambda_p::context::context ()
{
}

lambda_p::context::context (lambda_p::position first_a, lambda_p::position last_a)
	: first (first_a),
	last (last_a)
{
}

lambda_p::context::context (size_t first_row, size_t first_column, size_t first_character, size_t last_row, size_t last_column, size_t last_character)
	: first (first_row, first_column, first_character),
	last (last_row, last_column, last_character)
{
}

bool lambda_p::context::operator == (lambda_p::context const & other)
{
	bool result (first == other.first && last == other.last);
	return result;
}

std::wstring lambda_p::context::string ()
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