#pragma once

#include <lambda_p/builder.h>

namespace lambda_p_kernel
{
	class builder : public lambda_p::builder
	{
	public:
		builder ();
		std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> injected_declarations () override;
		std::map <std::wstring, boost::shared_ptr <lambda_p::parser::state_factory>> keywords () override;
	};
}

