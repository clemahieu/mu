#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p_llvm
{
	class type_graph_binder : public lambda_p::binder::binder
	{
	public:
		void bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
		void core (boost::shared_ptr <lambda_p::core::routine> routine, boost::shared_ptr <lambda_p::binder::list> parameters, lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems);
	};
}

