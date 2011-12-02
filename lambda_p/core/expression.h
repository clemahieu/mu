#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class expression
		{
		public:
			std::vector <boost::shared_ptr <lambda_p::core::expression>> contents;
			void add (boost::shared_ptr <lambda_p::core::expression> other);
		};
	}
}
