#include <mu/core/region.hpp>

mu::core::position::position ()
{
}

mu::core::region::region ()
{
}

mu::core::position::position (size_t offset_a, size_t row_a, size_t column_a):
offset (offset_a),
row (row_a),
column (column_a)
{
}

bool mu::core::position::operator == (mu::core::position const & other_a) const
{
    bool result (offset == other_a.offset && row == other_a.row && column == other_a.column);
    return result;
}

void mu::core::position::character ()
{
    ++offset;
    ++column;
}

void mu::core::position::line ()
{
    ++offset;
    ++row;
    column = 1;
}

mu::core::region::region (size_t offset1_a, size_t row1_a, size_t column1_a, size_t offset2_a, size_t row2_a, size_t column2_a):
first (offset1_a, row1_a, column1_a),
last (offset2_a, row2_a, column2_a)
{
}

mu::core::region::region (mu::core::position const & first_a, mu::core::position const & last_a):
first (first_a),
last (last_a)
{
}

bool mu::core::region::operator == (mu::core::region const & other_a) const
{
    bool result (first == other_a.first && last == other_a.last);
    return result;
}