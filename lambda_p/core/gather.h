#pragma once

#include <lambda_p/core/target.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class target;
		class expression;
		class connection;
		class gather
		{
		public:
			gather (boost::shared_ptr <lambda_p::core::target> target_a);
			void operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> & arguments, size_t sequence);
			boost::shared_ptr <lambda_p::core::connection> operator () (boost::shared_ptr <lambda_p::core::gather> self_a);
		private:
			std::vector <std::vector <boost::shared_ptr <lambda_p::core::expression>>> arguments;
			boost::shared_ptr <lambda_p::core::target> target;
			size_t remaining;
		};
	}
}

