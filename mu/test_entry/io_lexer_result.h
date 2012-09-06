#pragma once

#include <mu/io/tokens_visitor.h>
#include <mu/core/errors/error_list.h>

namespace mu
{
	namespace io
	{
		namespace tokens
		{
			class token;
		}
	}
	namespace io_test
	{
		class lexer_result : public mu::io::tokens::visitor
		{
		public:
            void operator () (mu::io::tokens::token const & token);
            void operator () (mu::io::tokens::divider const & token) override;
            void operator () (mu::io::tokens::identifier const & token) override;
            void operator () (mu::io::tokens::left_square const & token) override;
            void operator () (mu::io::tokens::right_square const & token) override;
            void operator () (mu::io::tokens::stream_end const & token) override;
            void operator () (mu::io::tokens::value const & token) override;
            void print (std::wostream & target);
			mu::vector <mu::io::tokens::token const *> results;
            mu::core::errors::error_list errors;
		};
	}
}
