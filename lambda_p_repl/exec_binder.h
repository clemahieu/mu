#pragma once

#include <lambda_p/binder/binder.h>
#include <lambda_p/binder/routine_instances.h>

namespace lambda_p_repl
{
	class exec_binder : public lambda_p::binder::binder
	{
	public:
		exec_binder (lambda_p::binder::routine_instances instances_a);
		void bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
		lambda_p::binder::routine_instances instances;
	};
}

