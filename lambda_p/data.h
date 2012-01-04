#pragma once

#include <string>

#include <lambda_p/node.h>

namespace lambda_p
{
	class data : public lambda_p::node
	{
	public:
		data (std::wstring string_a);
		std::wstring string;
	};
}

