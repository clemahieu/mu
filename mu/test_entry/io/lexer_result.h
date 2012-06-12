#pragma once

#include <mu/io/debugging/context.h>

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
			void operator () (mu::io::tokens::token *, mu::io::debugging::context context_a);
            void print (std::wostream & target);
			std::vector <std::pair <mu::io::tokens::token *, mu::io::debugging::context>> results;
		};
	}
}
