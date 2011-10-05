#pragma once

#include <vector>

namespace lambda_p
{
	namespace binder
	{
		class routine_binder;
		class data;
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
		class association;
		class statement
		{
			friend class ::lambda_p::binder::data;
			friend class ::lambda_p::binder::routine_binder;
            template <typename> friend class ::lambda_p::serialization::simple;
			friend class ::lambda_p::serialization::parser::simple_parser;
		public:
			statement (size_t target_a);
			~statement (void);
			size_t target;
			::lambda_p::core::association * association;
		};
	}
}
