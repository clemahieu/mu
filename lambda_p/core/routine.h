#pragma once

#include <vector>

#include <lambda_p/core/statement.h>
#include <lambda_p/core/declaration.h>
#include <lambda_p/core/reference.h>
#include <lambda_p/core/data.h>

namespace lambda_p_repl
{
	class repl;
}

namespace lambda_p
{
	namespace binder
	{
		class routine_binder;
	}
	namespace serialization
	{
		template <typename> class simple;
	}
	namespace parser
	{
		class simple_parser;
		class statement;
	}
	namespace core
	{
		class routine
		{
			friend class ::lambda_p::core::statement;
			friend class ::lambda_p::core::reference;
			friend class ::lambda_p::core::data;
			friend class ::lambda_p::core::declaration;
			friend class ::lambda_p::core::node;
            template <typename> friend class ::lambda_p::serialization::simple;
			friend class ::lambda_p::parser::simple_parser;
			friend class ::lambda_p::binder::routine_binder;
			friend class ::lambda_p::parser::statement;
			friend class ::lambda_p_repl::repl;
		public:
			routine ();
			~routine (void);
			::lambda_p::core::statement * add_statement ();
			::lambda_p::core::data * add_data (::std::wstring string, size_t statement_a, size_t index_a);
			::lambda_p::core::declaration * add_declaration (size_t self_statement_a, size_t self_argument_a);
			::lambda_p::core::reference * add_reference (size_t target_statement_a, size_t target_argument_a, size_t self_statement_a, size_t self_argument_a);
			void validate (::std::wostream & problems) const;
		private:
			::std::vector < ::lambda_p::core::statement *> statements;
			::std::vector < ::lambda_p::core::declaration *> declarations;
			::std::vector < ::lambda_p::core::reference *> references;
			::std::vector < ::lambda_p::core::data *> data;
		};
	}
}
