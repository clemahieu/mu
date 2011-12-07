#pragma once

#include <lambda_p/core/expression.h>

namespace lambda_p
{
	namespace core
	{
		class expression_list : public lambda_p::core::expression
		{
		public:
			lambda_p::core::expression_iterator begin () override;
			lambda_p::core::expression_iterator end () override;
			bool resolved () override;
			std::vector <lambda_p::core::expression *> contents;
		};
	}
}

