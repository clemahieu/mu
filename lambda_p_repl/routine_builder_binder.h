#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p_repl
{
	class character_stream;
	class routine_builder_binder : public lambda_p::binder::binder
	{
	public:
		void bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems) override;
		void core (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems, boost::shared_ptr <lambda_p_repl::character_stream> stream);
		std::wstring binder_name () override;
	};
}

