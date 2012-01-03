#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p_serialization
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
			void operator () (lambda_p_serialization::tokens::token * token);
			boost::shared_ptr <std::vector <lambda_p_serialization::tokens::token *>> tokens;
		};
	}
}

