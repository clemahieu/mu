#pragma once 

#include <mu/core/types.hpp>

namespace mu
{
    namespace core
    {
        class position
        {
        public:
			position ();
            position (uint64_t offset_a, uint64_t row_a, uint64_t column_a);
            bool operator == (mu::core::position const & other_a) const;
            mu::string string ();
            void character ();
            void line ();
            uint64_t offset;
            uint64_t row;
            uint64_t column;
        };
        class region
        {
        public:
            region ();
            region (uint64_t offset1_a, uint64_t row1_a, uint64_t column1_a, uint64_t offset2_a, uint64_t row2_a, uint64_t column2_a);
            region (mu::core::position const & first_a, mu::core::position const & last_a);
            bool operator == (mu::core::region const & other_a) const;
            mu::string string ();
            mu::core::position first;
            mu::core::position last;
        };        
    }
}