#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace mu
{
	namespace io
	{
		namespace tokens
		{
			class token;
		}
		namespace lexer
		{
			class token_vector
			{
			public:
				token_vector ();
				void operator () (mu::io::tokens::token * token);
				boost::shared_ptr <std::vector <mu::io::tokens::token *>> tokens;
			};
		}
	}
}
