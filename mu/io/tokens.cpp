#include <mu/io/tokens.hpp>

mu::io::position::position (size_t offset_a, size_t row_a, size_t column_a):
offset (offset_a),
row (row_a),
column (column_a)
{
}

bool mu::io::position::operator == (mu::io::position const & other_a) const
{
    bool result (offset == other_a.offset && row == other_a.row && column == other_a.column);
    return result;
}

void mu::io::position::character ()
{
    ++offset;
    ++column;
}

void mu::io::position::line ()
{
    ++offset;
    ++row;
    column = 1;
}

mu::io::region::region (size_t offset1_a, size_t row1_a, size_t column1_a, size_t offset2_a, size_t row2_a, size_t column2_a):
first (offset1_a, row1_a, column1_a),
last (offset2_a, row2_a, column2_a)
{
}

mu::io::region::region (mu::io::position const & first_a, mu::io::position const & last_a):
first (first_a),
last (last_a)
{
}

bool mu::io::region::operator == (mu::io::region const & other_a) const
{
    bool result (first == other_a.first && last == other_a.last);
    return result;
}


mu::io::token::token (mu::io::region const & region_a):
region (region_a)
{
}

mu::io::token::~token ()
{
}

mu::io::left_square::left_square (mu::io::region const & region_a):
token (region_a)
{
}

mu::io::token_id mu::io::left_square::id ()
{
    return mu::io::token_id::left_square;
}

mu::io::right_square::right_square (mu::io::region const & region_a):
token (region_a)
{
}

mu::io::token_id mu::io::right_square::id ()
{
    return mu::io::token_id::right_square;
}

mu::io::terminator::terminator (mu::io::region const & region_a):
token (region_a)
{
}

mu::io::token_id mu::io::terminator::id ()
{
    return mu::io::token_id::terminator;
}

mu::io::end::end (mu::io::region const & region_a):
token (region_a)
{
}

mu::io::token_id mu::io::end::id ()
{
    return mu::io::token_id::end;
}

mu::io::identifier::identifier (mu::io::region const & region_a):
token (region_a)
{
}

mu::io::token_id mu::io::identifier::id ()
{
    return mu::io::token_id::identifier;
}