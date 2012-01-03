#pragma once

#include <lambda_p/core/node.h>

#include <boost/function.hpp>

namespace lambda_p
{
	namespace errors
	{
		class error;
	}
	namespace core
	{
		class explode : public lambda_p::core::node
		{
		public:
			explode (std::vector <boost::shared_ptr <lambda_p::core::expression>> items_a, boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> & parameters, boost::shared_ptr <lambda_p::core::target> target_a) override;
			std::vector <boost::shared_ptr <lambda_p::core::expression>> items;
			boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors;
		};
	}
}

