#pragma once

#include <string>

#include <lambda_p/core/node.h>

namespace lambda_p
{
	namespace core
	{
		class data : public node
		{
		public:
			data(void);
			~data(void);
			::std::wstring item;
		};
	}
}

