#pragma once

#include <iostream>

#include <lambda_p/core/node.h>

namespace lambda_p
{
    namespace serialization
    {
        template <typename> class simple;
    }
	namespace core
	{
		class routine;
		class declaration : public node
		{
            template <typename> friend class ::lambda_p::serialization::simple;
		public:
			declaration (::lambda_p::core::routine * routine_a, size_t self_statement_a, size_t self_argument_a);
			~declaration (void);
			void validate (::std::iostream & problems) const;
			node_id node_type () const;
		private:
			::lambda_p::core::routine * routine;
			size_t self_statement;
			size_t self_argument;
		};
	}
}

