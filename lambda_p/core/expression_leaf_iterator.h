#pragma once

#include <lambda_p/core/expression_iterator_internal.h>

namespace lambda_p
{
	namespace core
	{
		class expression;
		class expression_leaf_iterator : public lambda_p::core::expression_iterator_internal
		{
		public:
			expression_leaf_iterator (lambda_p::core::expression * expression_a, bool end_a);
			void operator ++ () override;
			bool operator == (lambda_p::core::expression_iterator_internal * other) override;
			bool operator != (lambda_p::core::expression_iterator_internal * other) override;
			lambda_p::core::expression * operator * () override;
			lambda_p::core::expression * expression;
			bool end;
		};
	}
}

