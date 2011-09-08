#pragma once

#include <map>

namespace lambda_p
{
	namespace core
	{
		class node;
		class routine;
		class statement;
	}
	namespace binder
	{
		class node_binder;
		class routine_binder
		{
		public:
			routine_binder (::std::map < ::lambda_p::core::node *, ::lambda_p::binder::node_binder *> binders_a);
			~routine_binder (void);
			void bind (::lambda_p::core::routine * routine_a);
			::std::map < ::lambda_p::core::node *, ::lambda_p::binder::node_binder *> binders;
			::std::map < ::lambda_p::core::node *, ::lambda_p::core::statement *> unbound_statements;
		private:
			bool arguments_resolved (::lambda_p::core::statement * statement);
		};
	}
}

