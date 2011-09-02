#pragma once

#include <iostream>

namespace lambda_p
{
	namespace core
	{
		class routine;
		class node
		{
		public:
			node ();
			~node (void);
            virtual void validate (::std::iostream & problems) const = 0;
		protected:
			void validate_argument (char const * self_name, ::lambda_p::core::routine * routine_a, size_t self_statement_a, size_t self_argument_a, ::std::iostream & problems) const;
		};
	}
}
