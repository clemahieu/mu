#pragma once

#include <lambda_p/binder/node_binder.h>

namespace lambda_p
{
	namespace binder
	{
		class routine_binder : public ::lambda_p::binder::node_binder
		{
		public:
			routine_binder (void);
			void bind (::lambda_p::core::statement * statement, routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
			::std::wstring binder_name ();
		};
	}
}

