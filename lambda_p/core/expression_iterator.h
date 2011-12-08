#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class expression;
		class expression_iterator_internal;
		class expression_iterator
		{
		public:
			expression_iterator ();
			expression_iterator (lambda_p::core::expression_iterator_internal * iter_a);
			void operator ++ ();
			bool operator == (lambda_p::core::expression_iterator & other);
			bool operator != (lambda_p::core::expression_iterator & other);
			boost::shared_ptr <lambda_p::core::expression> operator * ();
			lambda_p::core::expression_iterator_internal * iter;
		};
	}
}

