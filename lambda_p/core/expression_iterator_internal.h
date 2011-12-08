#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class expression;
		class expression_iterator_internal
		{
		public:
			virtual void operator ++ () = 0;
			virtual bool operator == (lambda_p::core::expression_iterator_internal * other) = 0;
			virtual bool operator != (lambda_p::core::expression_iterator_internal * other) = 0;
			virtual boost::shared_ptr <lambda_p::core::expression> operator * () = 0;
		};
	}
}

