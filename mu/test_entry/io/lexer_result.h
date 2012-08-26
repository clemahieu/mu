#pragma once

#include <mu/io/context.h>
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
		class lexer_result
		{
		public:
			void operator () (mu::io::tokens::token *, mu::io::context context_a);
            void print (std::wostream & target);
			mu::vector <std::pair <mu::io::tokens::token *, mu::io::context>> results;
            mu::core::errors::error_list errors;
		};
	}
}
