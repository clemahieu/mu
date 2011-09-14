#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p_repl
{
	class routine_input_binder : public ::lambda_p::binder::node_binder
	{
	public:
		routine_input_binder (void);
		~routine_input_binder (void);
		void bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems);
	};
}

