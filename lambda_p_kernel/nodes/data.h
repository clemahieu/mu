#pragma once

#include <string>

#include <lambda_p/binder/node.h>

namespace lambda_p_kernel
{
	namespace nodes
	{
		class data : public lambda_p::binder::node
		{
		public:
			data (std::wstring string_a);
            std::wstring string () const;
		private:
			std::wstring string_m;
		};
	}
}

