#pragma once

#include <lambda_p/core/target.h>

namespace lambda_p
{
	namespace core
	{
		class gather;
		class connection : public lambda_p::core::target
		{
		public:
			connection (boost::shared_ptr <lambda_p::core::gather> gather_a, size_t number_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments) override;
			boost::shared_ptr <lambda_p::core::gather> gather;
			size_t number;
		};
	}
}

