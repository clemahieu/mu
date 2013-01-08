#pragma once

#include <mu/core/types.hpp>

namespace mu
{
    namespace io
    {
        class position
        {
        public:
            position (size_t offset_a, size_t row_a, size_t column_a);
            bool operator == (mu::io::position const & other_a) const;
            void character ();
            void line ();
            size_t offset;
            size_t row;
            size_t column;
        };
        class region
        {
        public:
            region (size_t offset1_a, size_t row1_a, size_t column1_a, size_t offset2_a, size_t row2_a, size_t column2_a);
            region (mu::io::position const & first_a, mu::io::position const & last_a);
            bool operator == (mu::io::region const & other_a) const;
            mu::io::position first;
            mu::io::position last;
        };
        enum class token_id
        {
            end,
            identifier,
            left_square,
            right_square,
            terminator
        };
        class token
        {
        public:
            token (mu::io::region const & region_a);
            virtual ~token ();
            virtual token_id id () = 0;
            mu::io::region region;
        };
        class left_square : public token
        {
        public:
            left_square (mu::io::region const & region_a);
            token_id id () override;
        };
        class right_square : public token
        {
        public:
            right_square (mu::io::region const & region_a);
            token_id id () override;
        };
        class terminator : public token
        {
        public:
            terminator (mu::io::region const & region_a);
            token_id id () override;
        };
        class identifier : public token
        {
        public:
            identifier (mu::io::region const & region_a);
            token_id id () override;
            mu::string string;
        };
        class end : public token
        {
        public:            
            end (mu::io::region const & region_a);
            token_id id () override;
        };
    }
}