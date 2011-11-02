#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p
{
	namespace binder
	{
		class node_list;
	}
}
namespace lambda_p_repl
{
	class exec_binder : public lambda_p::binder::binder
	{
	public:
		exec_binder ();
		void set (boost::shared_ptr <lambda_p::binder::node> environment, boost::shared_ptr <lambda_p::binder::node> exec);
		void bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
		boost::shared_ptr <lambda_p::binder::node> environment;
		boost::shared_ptr <lambda_p::binder::node> exec;
	};
}

