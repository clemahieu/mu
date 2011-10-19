#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p_kernel
{
	class routine;
	class routine_binder : public lambda_p::binder::binder
	{
	public:
		routine_binder (void);
		void bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems);
		void core (lambda_p_kernel::routine & routine, lambda_p::binder::routine_instances & instances_l, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems);
		std::wstring binder_name ();
	};
}
