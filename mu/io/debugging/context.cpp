#include <mu/io/debugging/context.h>

#include <sstream>
#include <algorithm>

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

bool mu::io::debugging::context::operator == (mu::io::debugging::context const & other) const
{
	bool result (first == other.first && last == other.last);
	return result;
}

mu::string mu::io::debugging::context::string () const
{
    std::stringstream result;
	result << first.row;
	result << ',';
	result << first.column;
	result << ',';
	result << first.character;
	result << ':';
	result << last.row;
	result << ',';
	result << last.column;
	result << ',';
	result << last.character;
    auto aresult (result.str ());
	return mu::string (aresult.begin (), aresult.end ());;
}
