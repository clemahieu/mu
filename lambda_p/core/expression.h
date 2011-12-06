#pragma once

#include <lambda_p/core/expression_iterator.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class expression
		{
		public:
			virtual lambda_p::core::expression_iterator begin () = 0;
			virtual lambda_p::core::expression_iterator end () = 0;
			std::vector <lambda_p::core::expression *> nested;
		};
	}
}
