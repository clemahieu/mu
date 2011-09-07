#pragma once

#include <vector>

#include <lambda_p/core/statement.h>
#include <lambda_p/core/parameter_ref.h>
#include <lambda_p/core/result.h>
#include <lambda_p/core/result_ref.h>
#include <lambda_p/core/data.h>

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
		class routine
		{
			friend class ::lambda_p::core::statement;
			friend class ::lambda_p::core::parameter_ref;
			friend class ::lambda_p::core::result_ref;
			friend class ::lambda_p::core::data;
			friend class ::lambda_p::core::result;
			friend class ::lambda_p::core::node;
            template <typename> friend class ::lambda_p::serialization::simple;
			template <typename> friend class ::lambda_p::serialization::parser::simple_parser;
		public:
			routine (size_t parameters_a);
			~routine (void);
			::lambda_p::core::statement * add_statement ();
			::lambda_p::core::data * add_data (::boost::shared_array <uint8_t> item_a, size_t size_a, size_t statement_a, size_t index_a);
			::lambda_p::core::parameter_ref * add_parameter_ref (size_t target_parameter_a, size_t self_statement_a, size_t self_argument_a);
			::lambda_p::core::result * add_result (size_t self_statement_a, size_t self_argument_a);
			::lambda_p::core::result_ref * add_result_ref (size_t target_statement_a, size_t target_argument_a, size_t self_statement_a, size_t self_argument_a);
			void validate (::std::iostream & problems) const;
		private:
			size_t parameters;
			::std::vector < ::lambda_p::core::statement *> statements;
			::std::vector < ::lambda_p::core::parameter_ref *> parameter_refs;
			::std::vector < ::lambda_p::core::result *> results;
			::std::vector < ::lambda_p::core::result_ref *> result_refs;
			::std::vector < ::lambda_p::core::data *> data;
		};
	}
}
