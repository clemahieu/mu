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
		virtual void bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
	};
}

