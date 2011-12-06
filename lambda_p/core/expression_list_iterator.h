#pragma once

#include <lambda_p/core/expression_iterator_internal.h>

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class expression_list;
		class expression_list_iterator : public lambda_p::core::expression_iterator_internal
		{
		public:
			expression_list_iterator (lambda_p::core::expression_list & list_a);
			void operator ++ () override;
			bool operator == (lambda_p::core::expression_iterator_internal * other) override;
			bool operator != (lambda_p::core::expression_iterator_internal * other) override;
			lambda_p::core::expression * operator * () override;
			std::vector <lambda_p::core::expression *>::iterator current;
			std::vector <lambda_p::core::expression *>::iterator end;
		};
	}
}

