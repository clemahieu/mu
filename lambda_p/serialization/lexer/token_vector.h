#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	namespace tokens
	{
		class token;
	}
	namespace serialization
	{
		namespace lexer
		{
			class token_vector
			{
			public:
				token_vector(void);
				~token_vector(void);
				void operator () (::lambda_p::tokens::token * token);
				::boost::shared_ptr < ::std::vector < ::lambda_p::tokens::token *> > tokens;
			};
		}
	}
}

