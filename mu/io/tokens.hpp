#pragma once

#include <mu/core/types.hpp>
#include <mu/core/region.hpp>

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
            terminator,
			left_paren,
			right_paren
        };
        class token
        {
        public:
            token (mu::core::region const &);
            virtual ~token ();
            virtual token_id id () = 0;
            mu::core::region region;
        };
        class left_square : public token
        {
        public:
            left_square (mu::core::region const &);
            token_id id () override;
        };
        class right_square : public token
        {
        public:
            right_square (mu::core::region const &);
            token_id id () override;
        };
        class terminator : public token
        {
        public:
            terminator (mu::core::region const &);
            token_id id () override;
        };
        class identifier : public token
        {
        public:
            identifier (mu::core::region const &);
            token_id id () override;
            mu::string string;
        };
        class end : public token
        {
        public:            
            end (mu::core::region const &);
            token_id id () override;
        };
		class left_paren : public token
		{
		public:
			left_paren (mu::core::region const &);
			token_id id () override;
		};
		class right_paren : public token
		{
		public:
			right_paren (mu::core::region const &);
			token_id id () override;
		};
    }
}