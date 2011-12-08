#pragma once

#include <lambda_p/core/expression_iterator_internal.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class node;
		class expression;
		class node_iterator : public lambda_p::core::expression_iterator_internal
		{
		public:
			node_iterator (boost::shared_ptr <lambda_p::core::node> expression_a, bool end_a);
			void operator ++ () override;
			bool operator == (lambda_p::core::expression_iterator_internal * other) override;
			bool operator != (lambda_p::core::expression_iterator_internal * other) override;
			boost::shared_ptr <lambda_p::core::expression> operator * () override;
			boost::shared_ptr <lambda_p::core::expression> expression;
			bool end;
		};
	}
}

