#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p
{
	namespace binder
	{
		class routine_instances_binder : public ::lambda_p::binder::binder
		{
		public:
			routine_instances_binder(void);
			void bind (::lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
			::std::wstring binder_name ();
		};
	}
}

