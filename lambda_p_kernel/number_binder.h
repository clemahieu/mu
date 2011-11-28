#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p_kernel
{
	namespace nodes
	{
		class number;
	}
	class number_binder : public lambda_p::binder::binder
	{
	public:
		void bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems) override;
		void core (std::wstring & string, boost::shared_ptr <lambda_p_kernel::nodes::number> & target, lambda_p::errors::error_list & problems);
		std::wstring binder_name () override;
	};
}

