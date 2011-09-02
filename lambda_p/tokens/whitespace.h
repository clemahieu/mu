#pragma once

#include <iostream>

#include <lambda_p/tokens/token.h>

namespace lambda_p
{
	namespace tokens
	{
		template <typename source_type>
		class whitespace : public ::lambda_p::tokens::token
		{
		public:
			whitespace (source_type & source_a, ::std::streampos first_a, ::std::streampos last_a)
				: source (source_a),
				first (first_a),
				last (last_a)
			{
			}
			~whitespace (void)
			{
			}
		private:
			source_type & source;
			::std::streampos first;
			::std::streampos last;
		};
	}
}

