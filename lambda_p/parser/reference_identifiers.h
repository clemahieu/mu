#pragma once

#include <string>

namespace lambda_p
{
	namespace parser
	{
		class reference_identifiers
		{
		public:
			reference_identifiers (::std::wstring & statement_a, ::std::wstring & argument_a);
			~reference_identifiers (void);
			bool operator < (::lambda_p::parser::reference_identifiers const & other) const;
			::std::wstring statement;
			::std::wstring argument;
		};
	}
}

