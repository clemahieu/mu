#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p
{
	namespace binder
	{
		class routine_instances;
	}
}
namespace lambda_p_kernel
{
	class null_binder : public lambda_p::binder::binder
	{
	public:
		null_binder(void);
		~null_binder(void);
		virtual void bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems);
		std::wstring binder_name ();
	};
}

