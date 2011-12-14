#pragma once

#include <lambda_p/core/input.h>

namespace lambda_p
{
	class container : public lambda_p::core::input
	{
	public:
		void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments) override;
		std::vector <boost::shared_ptr <lambda_p::core::expression>> results;
	};
}

