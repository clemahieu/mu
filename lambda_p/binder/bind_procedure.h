#pragma once

#include <boost/shared_ptr.hpp>

#include <map>
#include <sstream>
#include <vector>

#include <lambda_p/binder/routine_instances.h>

namespace lambda_p
{
	namespace core
	{
		class routine;
		class statement;
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
		class bind_procedure
		{
		public:
			bind_procedure (::boost::shared_ptr < ::lambda_p::core::routine> routine_a);
			~bind_procedure (void);
			void operator () ();
			bool error ();
			void error_message (::std::wostream & stream);
			void reset ();
			::std::map < size_t, size_t> unbound_statements;
			::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > errors;
			::boost::shared_ptr < ::lambda_p::core::routine> routine;
		private:
			void bind_statement (size_t statement);
			void populate_unbound (size_t statement, ::boost::shared_ptr < ::lambda_p::binder::node_binder> & binder);
			void retry_bind (size_t statement);
			void copy_declaration_binder (::boost::shared_ptr < ::lambda_p::binder::node_instance> & binder, size_t node);
		};
	}
}

