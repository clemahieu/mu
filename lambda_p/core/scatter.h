#pragma once

#include <lambda_p/core/target.h>

namespace lambda_p
{
	namespace core
	{
		class connection;
		class scatter : public lambda_p::core::target
		{
		public:
			scatter (size_t size);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments) override;
			std::vector <std::vector <boost::shared_ptr <lambda_p::core::connection>>> targets;
		};
	}
}

