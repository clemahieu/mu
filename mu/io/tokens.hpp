#include <mu/core/types.hpp>

namespace mu
{
    namespace io
    {
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
            virtual ~token ();
            virtual token_id id () = 0;
        };
        class left_square : public token
        {
        public:
            token_id id () override;
        };
        class right_square : public token
        {
        public:
            token_id id () override;
        };
        class terminator : public token
        {
        public:
            token_id id () override;
        };
        class identifier : public token
        {
        public:
            token_id id () override;
            mu::string string;
        };
        class end : public token
        {
        public:
            token_id id () override;
        };
    }
}