#pragma once

#include <boost/shared_ptr.hpp>

#include <map>
#include <sstream>
#include <vector>

namespace lambda_p
{
	namespace core
	{
		class node;
		class routine;
		class statement;
		class declaration;
	}
	namespace errors
	{
		class error;
	}
	namespace binder
	{
		class node_binder;
		class node_instance;
		class bound_routine;
		class routine_binder
		{
		public:
			routine_binder (::boost::shared_ptr < ::lambda_p::core::routine> routine_a);
			~routine_binder (void);
			void operator () ();
			bool error ();
			void error_message (::std::wostream & stream);
			void reset ();
			::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > instances;
			::std::map < ::lambda_p::core::declaration *, size_t> unbound_statements;
			::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > errors;
		private:
			void bind_statement (size_t statement);
			void populate_unbound (size_t statement, ::boost::shared_ptr < ::lambda_p::binder::node_binder> & binder);
			void retry_bind (size_t statement);
			void copy_declaration_binder (::boost::shared_ptr < ::lambda_p::binder::node_instance> & binder, ::lambda_p::core::declaration * reference);
			::boost::shared_ptr < ::lambda_p::core::routine> routine;
		};
	}
}

