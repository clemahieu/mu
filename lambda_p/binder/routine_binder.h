#pragma once

#include <boost/shared_ptr.hpp>

#include <map>
#include <sstream>

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
		class node_instance;
		class bound_routine;
		class routine_binder
		{
		public:
			routine_binder ();
			~routine_binder (void);
			void operator () (::boost::shared_ptr < ::lambda_p::core::routine> routine_a);
			bool error ();
			void error_message (::std::wstring & target);
			void reset ();
			::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > instances;
			::std::map < ::lambda_p::core::node *, ::lambda_p::core::statement *> unbound_statements;
		private:
			::std::wstringstream error_message_m;
			void bind_statement (::boost::shared_ptr < ::lambda_p::core::routine> routine_a, ::lambda_p::core::statement * statement);
			void populate_unbound (::boost::shared_ptr < ::lambda_p::core::routine> routine_a, ::lambda_p::core::statement * statement, ::boost::shared_ptr < ::lambda_p::binder::node_binder> & binder);
		};
	}
}

