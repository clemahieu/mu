#pragma once

#include <string>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
	namespace serialization
	{
		class parse_result
		{
		public:
			::boost::shared_ptr < ::lambda_p::core::routine> routine;
			::std::wstring message;
		};
	}
}

