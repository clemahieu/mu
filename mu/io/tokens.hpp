#include <mu/core/types.hpp>

namespace mu
{
    namespace io
    {
        class token
        {
        public:
            virtual ~token ();
        };
        class left_square : public token
        {
        };
        class right_square : public token
        {
        };
        class terminator : public token
        {
        };
        class identifier : public token
        {
        public:
            mu::string string;
        };
        class end : public token
        {
        };
    }
}