#pragma once

#include <lambda_p/binder/node_instance.h>

#include <boost/shared_ptr.hpp>

#include <iostream>
#include <map>

namespace lambda_p
{
	namespace core
	{
		class statement;
		class node;
	}
	namespace binder
	{
		class node_binder : public node_instance
		{
		public:
			node_binder(void);
			~node_binder(void);
			virtual void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems) = 0;
		protected:
			// Checks for the specified number of results and arguments and also checks to make sure all arguments are references
			void check_count_only_references (bool & problem, size_t result_count, size_t argument_count, wchar_t const * binder_name, ::lambda_p::core::statement * statement, ::std::wstringstream & problems);
			// Checks to make sure all arguments are references
			void check_only_references (bool & problem, wchar_t const * binder_name, ::lambda_p::core::statement * statement, ::std::wstringstream & problems);
			// Checks for the specified number of results and arguments
			void check_count (bool & problem, size_t result_count, size_t argument_count, wchar_t const * binder_name, ::lambda_p::core::statement * statement, ::std::wstringstream & problems);
		};
	}
}

