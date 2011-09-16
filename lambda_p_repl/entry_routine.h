#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/binder/routine_binder.h>

namespace lambda_p
{
	namespace core
	{
		class routine;
		class node;
	}
	namespace binder
	{
		class command_list;
		class structure;
	}
}
namespace lambda_p_repl
{
	class entry_routine
	{
	public:
		entry_routine (::boost::shared_ptr < ::lambda_p::core::routine> routine_a);
		~entry_routine (void);
		void operator () ();
		::lambda_p::core::node * environment_node (::boost::shared_ptr < ::lambda_p::core::routine> routine);
		::boost::shared_ptr < ::lambda_p::core::routine> routine;
		::lambda_p::binder::routine_binder routine_binder;
		::boost::shared_ptr < ::lambda_p::binder::structure> dereference_binder;
		::boost::shared_ptr < ::lambda_p::binder::command_list> commands;
	};
}

