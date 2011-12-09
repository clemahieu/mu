#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class expression;
		class list;
		class list_iterator
		{
		public:
			list_iterator ();
			list_iterator (boost::shared_ptr <lambda_p::core::list> list_a, bool end_a);
			void operator ++ ();
			bool operator == (lambda_p::core::list_iterator const & other);
			bool operator != (lambda_p::core::list_iterator const & other);
			boost::shared_ptr <lambda_p::core::list> list;
			boost::shared_ptr <lambda_p::core::expression> operator * ();
			std::vector <boost::shared_ptr <lambda_p::core::expression>>::iterator current;
			std::vector <boost::shared_ptr <lambda_p::core::expression>>::iterator end;
			boost::shared_ptr <lambda_p::core::list_iterator> target_current;
			boost::shared_ptr <lambda_p::core::list_iterator> target_end;
		private:
			void set_target ();
			void skip ();
		};
	}
}

