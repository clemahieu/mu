#pragma once

#include <vector>

namespace lambda_p
{
	namespace binder
	{
		class routine_binder;
	}
    namespace serialization
    {
        template <typename> class simple;
		namespace parser
		{
			class simple_parser;
		}
    }
	namespace core
	{
		class routine;
		class node;
		class data;
		class declaration;
		class association;
		class statement
		{
			friend class ::lambda_p::core::data;
			friend class ::lambda_p::core::node;
			friend class ::lambda_p::binder::routine_binder;
            template <typename> friend class ::lambda_p::serialization::simple;
			friend class ::lambda_p::serialization::parser::simple_parser;
		public:
			statement (::lambda_p::core::declaration * target_a);
			~statement (void);
			::lambda_p::core::declaration * target;
			::lambda_p::core::association * association;
		};
	}
}
