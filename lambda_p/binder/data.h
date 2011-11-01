#pragma once

#include <string>

#include <lambda_p/binder/node.h>

namespace lambda_p
{
	namespace binder
	{
		class data : public lambda_p::binder::node
		{
		public:
			data (std::wstring string_a);
			~data (void);
            std::wstring string () const;
		private:
			std::wstring string_m;
		};
	}
}

