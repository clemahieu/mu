#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p_kernel
{
	class list_binder : public ::lambda_p::binder::binder
	{
	public:
		void bind (::lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems);
		::std::wstring binder_name ();
	};
}
