#pragma once

#include <string>

namespace lambda_p
{
	namespace parser
	{
		class result_reference
		{
		public:
			result_reference (::std::wstring & statement_a, ::std::wstring & argument_a);
			~result_reference (void);
			bool operator < (::lambda_p::parser::result_reference const & other) const;
			::std::wstring statement;
			::std::wstring argument;
		};
	}
}

