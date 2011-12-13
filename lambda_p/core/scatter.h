#pragma once

#include <lambda_p/core/input.h>

namespace lambda_p
{
	namespace core
	{
		class target;
		class scatter : public lambda_p::core::input
		{
		public:
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments) override;
			std::vector <std::vector <boost::shared_ptr <lambda_p::core::target>>> targets;
		};
	}
}

