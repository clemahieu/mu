#pragma once

#include <lambda_p/builder.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p_repl
{
	class builder : public lambda_p::builder
	{
	public:
		builder (boost::shared_ptr <lambda_p::binder::node> environment_a, boost::shared_ptr <lambda_p::binder::node> exec_a);
		std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> injected_declarations (boost::shared_ptr <lambda_p::binder::node> environment_a, boost::shared_ptr <lambda_p::binder::node> exec_a);
		std::map <std::wstring, boost::shared_ptr <lambda_p::parser::state_factory>> keywords () override;
	};
}

