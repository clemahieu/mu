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
		class binder;
		class instance;
	}
}
namespace lambda_p_kernel
{
	class bind_procedure
	{
	public:
		bind_procedure (::boost::shared_ptr < ::lambda_p::core::routine> routine_a);
		~bind_procedure (void);
		void operator () (::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		::std::map < size_t, size_t> unbound_statements;
		::boost::shared_ptr < ::lambda_p::core::routine> routine;
	private:
		void bind_statement (size_t statement, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		void populate_unbound (size_t statement, ::boost::shared_ptr < ::lambda_p::binder::binder> & binder, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		void retry_bind (size_t statement, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		void copy_declaration_binder (::boost::shared_ptr < ::lambda_p::binder::instance> & binder, size_t node);
	};
}

