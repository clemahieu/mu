#include <mu/core/region.hpp>

#include <inttypes.h>

mu::core::position::position ()
{
}

mu::core::region::region ()
{
}

mu::core::position::position (uint64_t offset_a, uint64_t row_a, uint64_t column_a):
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

mu::string mu::core::position::string ()
{
    char buffer [32 * 3];
    sprintf (buffer, "%" PRIx64 " %" PRIx64 " %" PRIx64, row, column, offset);
    std::string result_string (buffer);
    mu::string result (result_string.begin (), result_string.end ());
    return result;
}

mu::core::region::region (uint64_t offset1_a, uint64_t row1_a, uint64_t column1_a, uint64_t offset2_a, uint64_t row2_a, uint64_t column2_a):
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

mu::string mu::core::region::string ()
{
    mu::string result (first.string ());
    result += U":";
    result += last.string ();
    return result;
}