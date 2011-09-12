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
		class result_ref;
		class result;
		class data;
		class parameter_ref;
		class statement
		{
			friend class ::lambda_p::core::data;
			friend class ::lambda_p::core::node;
			friend class ::lambda_p::binder::routine_binder;
            template <typename> friend class ::lambda_p::serialization::simple;
			friend class ::lambda_p::serialization::parser::simple_parser;
		public:
			statement (::lambda_p::core::routine * routine_a, size_t index_a);
			~statement (void);
            void add_argument (::lambda_p::core::node * node_a);
            void validate (::std::wostream & problems) const;
            ::lambda_p::core::routine * routine;
            size_t index;
            ::std::vector < ::lambda_p::core::node *> arguments;
		};
	}
}
