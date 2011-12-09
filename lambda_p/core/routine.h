#pragma once

#include <lambda_p/core/expression.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class list;
		class routine : public lambda_p::core::expression
		{
		public:
			routine ();
			std::vector <boost::shared_ptr <lambda_p::core::expression>> surface;
			boost::shared_ptr <lambda_p::core::list> expression;
		};
	}
}
