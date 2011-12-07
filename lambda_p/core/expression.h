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
			lambda_p::core::expression_iterator begin ();
			lambda_p::core::expression_iterator end ();
			bool resolved ();
			std::vector <lambda_p::core::expression *> contents;
		};
	}
}
