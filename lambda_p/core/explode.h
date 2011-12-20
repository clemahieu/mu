#pragma once

#include <lambda_p/core/node.h>

namespace lambda_p
{
	namespace errors
	{
		class error_list;
	}
	namespace core
	{
		class explode : public lambda_p::core::node
		{
		public:
			explode (std::vector <boost::shared_ptr <lambda_p::core::expression>> items_a, boost::shared_ptr <lambda_p::errors::error_list> errors_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> parameters, boost::shared_ptr <lambda_p::core::target> target_a) override;
			std::vector <boost::shared_ptr <lambda_p::core::expression>> items;
			boost::shared_ptr <lambda_p::errors::error_list> errors;
		};
	}
}

