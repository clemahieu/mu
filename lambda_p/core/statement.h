#pragma once

#include <vector>

namespace lambda_p
{
    namespace serialization
    {
        template <typename> class simple;
		namespace parser
		{
			template <typename> class simple_parser;
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
			friend class ::lambda_p::core::result_ref;
			friend class ::lambda_p::core::data;
			friend class ::lambda_p::core::result;
			friend class ::lambda_p::core::parameter_ref;
			friend class ::lambda_p::core::node;
            template <typename> friend class ::lambda_p::serialization::simple;
			template <typename> friend class ::lambda_p::serialization::parser::simple_parser;
		public:
			statement (::lambda_p::core::routine * routine_a, size_t index_a);
			~statement (void);
            void add_argument (::lambda_p::core::node * node_a);
            void validate (::std::iostream & problems) const;
		private:
            ::lambda_p::core::routine * routine;
            size_t index;
            ::std::vector < ::lambda_p::core::node *> arguments;
		};
	}
}
