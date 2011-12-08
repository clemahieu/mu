#pragma once

#include <lambda_p/core/expression_iterator_internal.h>
#include <lambda_p/core/expression_iterator.h>

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class expression;
		class list;
		class list_iterator : public lambda_p::core::expression_iterator_internal
		{
		public:
			list_iterator (lambda_p::core::list & list_a, bool end_a);
			void operator ++ () override;
			bool operator == (lambda_p::core::expression_iterator_internal * other) override;
			bool operator != (lambda_p::core::expression_iterator_internal * other) override;
			boost::shared_ptr <lambda_p::core::expression> operator * () override;
			std::vector <boost::shared_ptr <lambda_p::core::expression>>::iterator current;
			std::vector <boost::shared_ptr <lambda_p::core::expression>>::iterator end;
			lambda_p::core::expression_iterator target_current;
			lambda_p::core::expression_iterator target_end;
		private:
			void check_end ();
			void skip ();
		};
	}
}

