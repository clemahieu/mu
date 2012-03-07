#pragma once

#include <mu/core/context.h>

#include <vector>

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
			void operator () (mu::io::tokens::token *, mu::core::context context_a);
            void print (std::wostream & target);
			std::vector <std::pair <mu::io::tokens::token *, mu::core::context>> results;
		};
	}
}
