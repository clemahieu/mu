#pragma once

#include <lambda_p/binder/binder.h>
#include <lambda_p_kernel/bool_c.h>

#include <string>
#include <map>

namespace lambda_p_kernel
{
	class bool_binder : public lambda_p::binder::binder
	{
	public:
		bool_binder ();
		void bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
		std::map <std::wstring, lambda_p_kernel::bool_c> map;
	};
}

