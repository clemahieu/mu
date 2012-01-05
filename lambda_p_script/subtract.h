#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p_kernel
{
	class subtract : public lambda_p::binder::binder
	{
	public:
		void bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
	};
}
