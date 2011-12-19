#pragma once

#include <lambda_p/core/target.h>

namespace lambda_p
{
	namespace core
	{
		class fixed;
		class entry : public lambda_p::core::target
		{
		public:
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments) override;
			std::vector <boost::shared_ptr <lambda_p::core::fixed>> fixed_parameters;
			boost::shared_ptr <lambda_p::core::target> next;
		};
	}
}

