#pragma once

#include <vector>

#include <lambda_p/core/statement.h>
#include <lambda_p/core/parameter_ref.h>
#include <lambda_p/core/result.h>
#include <lambda_p/core/result_ref.h>
#include <lambda_p/core/data.h>

namespace lambda_p
{
	namespace core
	{
		class routine
		{
			friend class ::lambda_p::core::statement;
			friend class ::lambda_p::core::parameter_ref;
			friend class ::lambda_p::core::result_ref;
			friend class ::lambda_p::core::data;
			friend class ::lambda_p::core::result;
		public:
			routine (size_t parameters_a);
			~routine (void);
			::lambda_p::core::statement * add_statement ();
			::lambda_p::core::data * add_data (::boost::shared_array <uint8_t> item_a, size_t size_a, size_t statement_a, size_t index_a);
			::lambda_p::core::parameter_ref * add_parameter_ref (size_t index_a);
			::lambda_p::core::result * add_result (size_t statement_a, size_t index_a);
			::lambda_p::core::result_ref * add_result_ref (size_t statement_a, size_t index_a);
		private:
			size_t parameters;
			::std::vector < ::lambda_p::core::statement> statements;
			::std::vector < ::lambda_p::core::parameter_ref> parameter_refs;
			::std::vector < ::lambda_p::core::result> results;
			::std::vector < ::lambda_p::core::result_ref> result_refs;
			::std::vector < ::lambda_p::core::data> data;
		};
	}
}
