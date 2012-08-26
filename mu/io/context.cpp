#include <mu/io/context.h>

#include <sstream>
#include <algorithm>

mu::io::context::context ()
{
}

mu::io::context::context (mu::io::position first_a, mu::io::position last_a):
first (first_a),
last (last_a)
{
}

mu::io::context::context (size_t first_row, size_t first_column, size_t first_character, size_t last_row, size_t last_column, size_t last_character):
first (first_row, first_column, first_character),
last (last_row, last_column, last_character)
{
}

bool mu::io::context::operator == (mu::io::context const & other) const
{
	bool result (first == other.first && last == other.last);
	return result;
}

mu::string mu::io::context::string () const
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
