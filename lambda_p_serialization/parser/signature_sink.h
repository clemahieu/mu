#pragma once

#include <vector>
#include <string>

namespace lambda_p_serialization
{
	namespace parser
	{
		class signature_sink
		{
		public:
			virtual void operator () (std::vector <std::wstring> parameters, std::wstring full_parameter) = 0;
		};
	}
}

