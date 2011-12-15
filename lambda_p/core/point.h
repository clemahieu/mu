#pragma once

#include <lambda_p/core/connection.h>

namespace lambda_p
{
	namespace core
	{
		class gather;
		class point : public lambda_p::core::connection
		{
		public:
			point (boost::shared_ptr <lambda_p::core::gather> target_a, size_t index_a);
			void operator () (boost::shared_ptr <lambda_p::core::expression> expression_a) override;
			boost::shared_ptr <lambda_p::core::gather> target;
			size_t index;
		};
	}
}

