#pragma once 

#include <cstring>

namespace mu
{
    namespace core
    {
        class position
        {
        public:
			position ();
            position (size_t offset_a, size_t row_a, size_t column_a);
            bool operator == (mu::core::position const & other_a) const;
            void character ();
            void line ();
            size_t offset;
            size_t row;
            size_t column;
        };
        class region
        {
        public:
            region ();
            region (size_t offset1_a, size_t row1_a, size_t column1_a, size_t offset2_a, size_t row2_a, size_t column2_a);
            region (mu::core::position const & first_a, mu::core::position const & last_a);
            bool operator == (mu::core::region const & other_a) const;
            mu::core::position first;
            mu::core::position last;
        };        
    }
}