#pragma once

#include <iostream>

namespace lambda_p
{
	namespace core
	{
		enum node_id
		{
			node_data,
			node_declaration,
			node_reference
		};
		class routine;
		class node
		{
		public:
			node ();
			~node (void);
            virtual void validate (::std::iostream & problems) const = 0;
			virtual node_id node_type () const = 0;
			virtual ::std::wstring node_type_name () const = 0;
		protected:
			void validate_argument (char const * self_name, ::lambda_p::core::routine * routine_a, size_t self_statement_a, size_t self_argument_a, ::std::iostream & problems) const;
		};
	}
}
