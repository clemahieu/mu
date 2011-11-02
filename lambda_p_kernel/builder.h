#pragma once

#include <lambda_p/builder.h>

namespace lambda_p_kernel
{
	class builder : public lambda_p::builder
	{
	public:
		std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> injected_declarations () override;
	};
}

